/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Message.h"
#include <stdio.h>
#include <iostream>
#include "Util.h"

#include "Signal.h"

Message* Message::parse( std::stringstream& ss, const Parsing_Options& po ){
    char line[256];
    char name[256];
    uint32_t id;
    int dlc;
    
    ss.getline( line, sizeof(line), '\n' );    
    int n_scanned = sscanf( line, "%i %[^:]: %i ", &id, name, &dlc);
    if( n_scanned != 3 ){
        std::cerr << "Fehler beim Scannen der Message" << std::endl;
        return NULL;
    }    
    Message* new_message = new Message();
    new_message->m_id  = id & calc_mask(29);
    new_message->m_ext = id & (1L<<31);
    new_message->m_name = std::string(name);
    new_message->m_dlc = dlc;
    
    if( po.b_verbose ){
        new_message->print();
    }
    
    // Parse and append signals to message
    char next_char;
    while( (next_char = ss.peek()) != '\n' && next_char != '\r' && next_char != -1 ){
        //std::cout << "next_char: " << (int)next_char << std::endl;
        //std::cout << "Parse next " << std::endl; 
        std::string token;
        ss >> token;
        //std::cout << "Token: '" << token << "'" << std::endl;
        if( token.empty() ) return new_message;
        if( token.compare(0, 3, "SG_") != 0 ){
            std::cerr << "Error while parsing signals of message " << new_message->m_name << std::endl;
            std::cerr << " Could not find 'SG_' in '" << token << "'"  << std::endl;
            return new_message;
        }
        Signal* new_signal = Signal::parse( ss, po );
        if( new_signal == NULL ){
            std::cerr << "Error while parsing signals of message " << new_message->m_name << std::endl;
            continue;
        }
        if( po.b_verbose ){
            new_signal->print();
        }
        new_signal->set_parent( new_message );
        new_message->m_signals.push_back(new_signal);
    }
    //std::cout << "End parsing" << std::endl;
    
    return new_message;
}
    
void Message::print(){
    std::cout << "Message:" << std::endl;
    std::cout << "    Name: " << m_name << std::endl;
    std::cout << "    ID:   " << m_id << std::endl;
    std::cout << "    DLC:  " << m_dlc << std::endl;
}

void Message::output_c( std::ostream& os, const Output_Options& oo ){
    if( oo.b_documentation ){          
        os << "/**" << std::endl;
        os << " * \\section Message " << m_name << "" << std::endl;
        os << " */" << std::endl;
        
        if( m_comment ){
            m_comment->output_c(os, oo);
            os << std::endl;
        }
        
        os << "/**" << std::endl;
        os << " * \\brief ID of message '" << m_name << "'" << std::endl;
        os << " */" << std::endl;
    }
    os << "#define ID_"  << m_name << " 0x" << std::hex << m_id << std::endl;
    os << std::endl;
    
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\brief Is ID of message '" << m_name << "' extended?" << std::endl;
        os << " */" << std::endl;
    }
    os << "#define EXT_" << m_name << " " << (m_ext ? "true" : "false") << std::endl;
    os << std::endl;
    
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\brief DLC of message '" << m_name << "'" << std::endl;
        os << " */" << std::endl;
    }
    os << "#define DLC_" << m_name << " " << m_dlc << std::endl;    
    os << std::endl;
    
    // TODO: SETTER und GETTER für Message aufzählen
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\brief SETTERs for message '" << m_name << "'" << std::endl;
    }else{
        os << " /*" << std::endl;
    }
    for( int i = m_signals.size()-1; i >= 0; i-- ){
        os << " * - SET_" << m_name << "_" << m_signals[i]->get_name() << "(buf, value)" << std::endl;
    }
    os << " */" << std::endl;
    os << std::endl;
    
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\brief GETTERs for message '" << m_name << "'" << std::endl;
    }else{
        os << " /*" << std::endl;
    }
    for( int i = m_signals.size()-1; i >= 0; i-- ){
        os << " * - GET_" << m_name << "_" << m_signals[i]->get_name() << "(buf)" << std::endl;
    }
    os << " */" << std::endl;
    os << std::endl;
    
    // Signals are stored in the wrong order -> iterate from the end
    for( int i = m_signals.size()-1; i >= 0; i-- ){
        m_signals[i]->output_c( os, oo );
        os << std::endl;
    }
}