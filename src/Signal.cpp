/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Signal.h"
#include <iostream>
#include <iomanip>

#include "Util.h"

Signal* Signal::parse( std::stringstream& ss, const Parsing_Options& po ){
    char line[512];
    char name[256] = {0};
    char unit[256] = {0};
    int startbit;
    int length;
    int endianess;
    char signess;
    float factor, offset, min, max;
    
    ss.getline( line, sizeof(line), '\n' );    
    
    int n_scanned = sscanf( line, "%s : %i|%i@%i%c (%f,%f) [%f|%f] \"%[^\"]\"", name, &startbit, &length, &endianess, &signess, &factor, &offset, &min, &max, unit);
    if( n_scanned < 9 ){
        std::cerr << "Fehler beim Scannen des Signals" << std::endl;
        std::cerr << n_scanned << " von 10 gescannt" << std::endl;
        return NULL;
    }
    Signal* new_signal = new Signal();
    
    new_signal->m_name = std::string(name);
    new_signal->m_startbit = startbit;
    new_signal->m_length_bit = length;
    new_signal->m_endianess = (Endianess)endianess;
    new_signal->m_signess = signess == '+' ? UNSIGNED : SIGNED;
    new_signal->m_factor = factor;
    new_signal->m_offset = offset;
    new_signal->m_max = max;
    new_signal->m_min = min;
    new_signal->m_unit = std::string(unit);
    
    return new_signal;
}
        
void Signal::print(){
    std::cout << "Signal: " << std::endl;
    std::cout << "    Name:            " << m_name << std::endl;
    std::cout << "    Startbit:        " << m_startbit << std::endl;
    std::cout << "    Length (in bit): " << m_length_bit << std::endl;
    std::cout << "    Endianess:       " << m_endianess << std::endl;
    std::cout << "    Signess:         " << m_signess  << std::endl;
    std::cout << "    Unit:            " << m_unit  << std::endl;
    std::cout << "    Factor:          " << m_factor  << std::endl;
    std::cout << "    Offset:          " << m_offset  << std::endl;
    std::cout << "    Min:             " << m_min  << std::endl;
    std::cout << "    Max:             " << m_max  << std::endl;    
}

std::string Signal::datatype(){
    std::string s_datatype;
    
    if( m_signess == UNSIGNED ){
        s_datatype += "u";
    }
    
    if( m_length_bit <= 8 ){
        s_datatype += "int8_t";
    }else if( m_length_bit <= 16 ){
        s_datatype += "int16_t";
    }else if( m_length_bit <= 32 ){
        s_datatype += "int32_t";
    }else{
        s_datatype += "int64_t";
    }
    
    return s_datatype;
}

int Signal::datatype_length(){
    if( m_length_bit <= 8 ){
        return 8;
    }else if( m_length_bit <= 16 ){
        return 16;
    }else if( m_length_bit <= 32 ){
        return 32;
    }
    return 64;
}

static std::string unsigned_datatype( int size_bit ){
    std::string data_type;
    
    switch( (size_bit-1)/8 ){
        case 0:
            data_type = "uint8_t";
            break;
        case 1:
            data_type = "uint16_t";
            break;
        case 2:
        case 3:
            data_type = "uint32_t";
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            data_type = "uint64_t";
            break;
    }
    return data_type;
}

void Signal::set_intel( std::ostream& os, const Output_Options& oo ){
    //int B = 0;
    int startbit = m_startbit%8;
    int bits_processed = 0;
    
    for( int b = m_startbit/8; b <= (m_startbit+m_length_bit-1)/8; b++ ){
        // b ist byte in datenarray (beginnend bei 0)
        // r ist Anzahl der shifts nach rechts
        // l ist Anzahl der shifts nach links
        
        int r = bits_processed;
        int l = startbit;
        
        int bits = MIN( 8-startbit, m_length_bit - bits_processed );
        int mask = (1 << bits) -1;
        
        os << "   buf[" << b << "] &= ~(uint8_t)(0x" << std::setfill('0') << std::setw(2) << std::hex << mask << " << " << std::dec << l << ");\\" << std::endl;
        os << "   buf[" << b << "] |=  (uint8_t)(((val) >> " << std::setfill(' ') << std::setw(2) << std::dec << r << ") & 0x" << std::setfill('0') << std::setw(2) << std::hex << mask << std::dec << ") << " <<  std::dec << l << ";\\" << std::endl;
        
        startbit = 0;
        bits_processed += bits;
        
        //B++;
    }
}

void Signal::get_intel( std::ostream& os, const Output_Options& oo ){
    int startbit = m_startbit%8;
    int bits_processed = 0;
    int B = 0;
    
    for( int b = m_startbit/8; b <= (m_startbit+m_length_bit-1)/8; b++ ){
        // b ist byte in datenarray (beginnend bei 0)
        // r ist Anzahl der shifts nach rechts
        // l ist Anzahl der shifts nach links
        
        int r = bits_processed;
        int l = startbit;
        
        int bits = MIN( 8-startbit, m_length_bit - bits_processed );
        int mask = (1 << bits) -1;
        
        os << "   | ((+("<<unsigned_datatype(m_length_bit)<< ")(buf[" << b << "] >> " <<  std::dec << l << ") & 0x" << std::setfill('0') << std::setw(2) << std::hex << mask << std::dec <<") << " <<  std::dec << r << ") \\" << std::endl;
        //os << "   | (((buf[" << b << "] >> " <<  std::dec << l << ") & 0x" << std::setfill ('0') << std::setw(2) << std::hex << mask << std::dec <<") << " <<  std::dec << r << ") \\" << std::endl;
        
        startbit = 0;
        bits_processed += bits;
        
        B++;
    }
}

// os << "   buf[" << b << "] |= (uint8_t)((val) >> " << r << ") << " << l << ";\\" << std::endl;
void Signal::set_motorola( std::ostream& os, const Output_Options& oo ){
    int B = 0;
    int r = 0;
    int l = 0;
    int bits_processed = 0;
    int startbit = m_startbit % 8;
    
    for( int b = m_startbit/8; b <= m_startbit/8+(m_length_bit + 6 - m_startbit%8 )/8 ;b++ ){
    //for( int b = m_startbit/8; b >= (m_startbit+8-2*(m_startbit%8)-m_length_bit)/8; b++ ){
        // b ist byte in datenarray (beginnend bei 0)
        // r ist Anzahl der shifts nach rechts
        // l ist Anzahl der shifts nach links

        //int r = MAX((m_startbit%8-8)+B*8, 0);
        //int l = ( 8 - (m_length_bit - m_startbit - 1)%8 )%8;
        
        l = MAX( 0, startbit - MIN( 7, m_length_bit - bits_processed - 1 ));
        
        bits_processed += startbit + 1;
        r = MAX(0, m_length_bit - bits_processed);
        
        int mask = (1 << MIN(8,startbit - l + 1)) - 1;
        
        os << "   buf[" << b << "] &= ~(uint8_t)(0x" << std::setfill('0') << std::setw(2) << std::hex << mask << " << " << std::dec << l << ");\\" << std::endl;
        os << "   buf[" << b << "] |=  (uint8_t)(((val) >> " << std::setfill(' ') << std::setw(2) << std::dec << r << ") & 0x" << std::setfill('0') << std::setw(2) << std::hex << mask << std::dec << ") << " << std::dec << l << ";\\" << std::endl;
        
        startbit = 7;
        B++;
    }   
}

// int mask = (1 << MIN(8,m_length_bit - bits_processed)) - 1;
// os << "   | ((("<<datatype(B)<< ")(buf[" << b << "] >> " << l << ") & 0x" << std::hex << mask << std::dec <<") << " << r << ") \\" << std::endl;
void Signal::get_motorola( std::ostream& os, const Output_Options& oo ){
    int B = 0;
    int r = 0;
    int l = 0;
    int bits_processed = 0;
    int startbit = m_startbit % 8;
    
    for( int b = m_startbit/8; b <= m_startbit/8+(m_length_bit + 6 - m_startbit%8 )/8 ;b++ ){
    //for( int b = m_startbit/8; b >= (m_startbit+8-2*(m_startbit%8)-m_length_bit)/8; b++ ){
        // b ist byte in datenarray (beginnend bei 0)
        // r ist Anzahl der shifts nach rechts
        // l ist Anzahl der shifts nach links

        //int r = MAX((m_startbit%8-8)+B*8, 0);
        //int l = ( 8 - (m_length_bit - m_startbit - 1)%8 )%8;
        
        l = MAX( 0, startbit - MIN( 7, m_length_bit - bits_processed - 1 ));
        
        bits_processed += startbit + 1;
        r = MAX(0, m_length_bit - bits_processed);
        
        int mask = (1 << MIN(8,startbit - l + 1)) - 1;
        
        os << "   | ((+("<<unsigned_datatype(m_length_bit)<< ")(buf[" << b << "] >> " <<  std::dec << l << ") & 0x" << std::setfill ('0') << std::setw(2) << std::hex << mask << std::dec <<") << " <<  std::dec << r << ") \\" << std::endl;
        //os << "   | (((buf[" << b << "] >> " <<  std::dec << l << ") & 0x" << std::setfill ('0') << std::setw(2) << std::hex << mask << std::dec <<") << " <<  std::dec << r << ") \\" << std::endl;
        
        startbit = 7;
        B++;
    }  
}

void Signal::output_c( std::ostream& os, const Output_Options& oo ){
    std::string signal_name = (m_parent ? m_parent->get_name() : "Unknown") + "_" + m_name;
    
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\subsection Signal " << m_name << std::endl;
        os << " */" << std::endl;
    
        if( m_comment ){
            m_comment->output_c(os, oo);
            os << std::endl;
        }
        
        os << "/**" << std::endl;
        os << " * \\paragraph Constants" << std::endl;
        os << " */" << std::endl;
    }
    
    os << "#define UNIT_" << signal_name << "   \"" << m_unit << "\"" << std::endl;
    os << "#define OFFSET_" << signal_name << " " << m_offset << std::endl;
    os << "#define FACTOR_" << signal_name << " " << m_factor << std::endl;
    os << "#define MIN_" << signal_name << "    " << m_min << std::endl;
    os << "#define MAX_" << signal_name << "    " << m_max << std::endl;
    os << std::endl;
    
    if( m_valtype == NULL ){
        // "Funktion, die REAL_TO_CAN    
        os << "#define CAN_TO_REAL_" << signal_name << "(x) ((x) * "<<m_factor<<" + " <<m_offset<<")" << std::endl;
        os << "#define REAL_TO_CAN_" << signal_name << "(x) ("<<datatype()<<")(((x) - "<<m_offset<<") / "<<m_factor<<")" << std::endl;    
        os << std::endl;
    }
    
    os << "#define SET_" << signal_name << "_Raw(buf,val) {\\" << std::endl;    
    if( m_endianess == INTEL ){
        set_intel(os, oo);
    }else{
        set_motorola(os, oo);
    }
    os << "}" << std::endl;
    os << std::endl;
    
    if( m_valtype != NULL ){
        // IEEE Float/Double-Format
        os << "#define SET_" << signal_name << "(buf,val) \\" << std::endl;
        if( m_valtype->type() == Sig_ValType::TYPE_IEEE_FLOAT ){
            os << "{\\" << std::endl;
            os << "    float val_ = (float)val; \\" << std::endl;
            os << "    SET_" << signal_name << "_Raw(buf, ((uint32_t)*(uint32_t*)&val_) ) \\" << std::endl;
            os << "}\\" << std::endl;
        }
        if( m_valtype->type() == Sig_ValType::TYPE_IEEE_DOUBLE ){
            os << "{\\" << std::endl;
            os << "    double val_ = (double)val; \\" << std::endl;
            os << "    SET_" << signal_name << "_Raw(buf, ((uint64_t)*(uint64_t*)&val) ) \\" << std::endl;
            os << "}\\" << std::endl;
        }
        os << std::endl;
    }else{
        os << "#define SET_" << signal_name << "(buf,val) \\" << std::endl;        
        os << "   SET_" << signal_name << "_Raw(buf,REAL_TO_CAN_" << signal_name << "(val))" << std::endl;
        os << std::endl;
    }
    
    os << "#define GET_" << signal_name << "_Raw(buf) ("<< datatype() << ") (0\\" << std::endl;
    if( m_endianess == INTEL ){
        get_intel(os, oo);        
    }else{
        get_motorola(os, oo);
    }
    os << ")" << std::endl;
    os << std::endl;
    
    if( m_valtype != NULL ){
        // IEEE Float/Double-Format
        os << "#define GET_" << signal_name << "(buf) \\" << std::endl;
        if( m_valtype->type() == Sig_ValType::TYPE_IEEE_FLOAT ){
            os << "   (float)*((float*)&(uint32_t){" << "GET_" << signal_name << "_Raw(buf)})" << std::endl;
        }
        if( m_valtype->type() == Sig_ValType::TYPE_IEEE_DOUBLE ){
            os << "   (double)*((double*)&(uint64_t){" << "GET_" << signal_name << "_Raw(buf)})" << std::endl;
        }
        os << std::endl;
    }else{
        // Warnung ausgeben, wenn das Signal singed ist und die Länge weder 8, 16, 32 oder 64 ist.
        if( m_signess == SIGNED && m_length_bit != 1 &&  m_length_bit != 8 && m_length_bit != 16 && m_length_bit != 32 && m_length_bit != 64 ){
            //os << "#warning \"signed signals with bitlength that are not 8, 16, 32 or 64 not yet supported." << std::endl;
            os << "// Necessary for singed signals with length that is not 1, 8, 16, 32 or 64 bits." << std::endl;
            os << "#define SIGNED_" << signal_name << "(val) \\" << std::endl;
            os << "   ((((val)&0x" << std::hex << (1<<(m_length_bit-1)) << ")>0) ? ((" << datatype() << ")((val)|0x" << std::hex << calc_mask(datatype_length()) - calc_mask(m_length_bit) << ")) : ((" << datatype() << ")(val)))" << std::endl;
            os << std::endl;
        
            os << "#define GET_" << signal_name << "(buf) \\" << std::endl;
            os << "   CAN_TO_REAL_" << signal_name << "(SIGNED_" << signal_name << "(GET_" << signal_name << "_Raw(buf)))" << std::endl;
        }else{
            os << "#define GET_" << signal_name << "(buf) \\" << std::endl;
            os << "   CAN_TO_REAL_" << signal_name << "(GET_" << signal_name << "_Raw(buf))" << std::endl;
        }
    }
}

// sscanf( test_string, "%s : %i|%i@%i%c (%f,%f) [%f|%f] \"%[^\"]\"", name, &startbit, &length, &intel, &signess, &factor, &offset, &min, &max, unit);