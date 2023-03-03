/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Val_Table.h"
#include <iostream>
#include <iomanip>

#include "Util.h"

#include <map>

#include <limits.h>

#include <algorithm>

bool sorting_function( const Value_Definition& a, const Value_Definition& b ){
    return a.value < b.value;
}

Val_Table* Val_Table::parse( std::stringstream& ss, const Parsing_Options& po){
    unsigned int id_message;
    std::string name_signal;
    
    char next_char;
    if( (next_char = ss.peek()) == '\n' || next_char == '\r' || next_char == -1 || next_char == 0 ){
        //std::cout << "Invalid character: " << next_char << std::endl;
        return NULL;
    }
    
    ss >> id_message;
    id_message &= calc_mask(29);
    if( ss.fail() ){
        std::cerr << "Failed to parse message-id of Value-Table." << std::endl;
        return NULL;
    }

    ss >> name_signal;
    if( ss.fail() ){
        std::cerr << "Failed to parse signal-name of Value-Table." << std::endl;
        return NULL;
    }

    std::vector<Value_Definition> value_definitions;
    while( (next_char = ss.peek()) != '\n' && next_char != '\r' && next_char != ';' && next_char != -1 ){
        Value_Definition v_d;
        
        ss >> v_d.value;
        if(po.b_verbose){
            std::cout << "v_d.value: " << v_d.value << std::endl;
        }
        
        if( (next_char = ss.peek()) == '\n' || next_char == '\r' || next_char == ';' || next_char == -1 ){
            return NULL;
        }
        
        ss >> std::quoted(v_d.description);        
        ss.ignore( INT_MAX, ' ');
        
        if(po.b_verbose){
            std::cout << "v_d.description: " << v_d.description << std::endl;
        }
        
        value_definitions.push_back( v_d );
    }
    
    std::sort( value_definitions.begin(), value_definitions.end(), sorting_function );
    
    Val_Table* new_val_table = new Val_Table( id_message, name_signal, value_definitions );
    
    if( po.b_verbose ){
        new_val_table->print();
    }
    
    // Cleanup
    if( ss.peek() == ';' ){
        std::string dummy;
        ss >> dummy;
    }
    
    
    
    //std::cout << "Val_Table: " << id_message << " " << name_signal << std::endl;
    return new_val_table;
}
    
void Val_Table::print(){
    std::cout << "Val_Table:" << std::endl;
    std::cout << "   Message-ID: " << m_id_message << std::endl;
    std::cout << "   Signal-Name: " << m_name_signal << std::endl;
    std::cout << "   Values:" << std::endl;
    for( int i = 0; i < m_values.size(); i++ ){
        std::cout << "      " << m_values[i].value << ": " << m_values[i].description << std::endl;
        
    }
}

static std::string to_upper_case( std::string s ){
    std::string output( s );
    for( int i = 0; i < output.length(); i++ ){
        if( 'a' <= output[i] && output[i] <= 'z' ){
            output[i] = output[i] - 'a' + 'A';
        }
    }
    return output;
}

void Val_Table::output_c( std::ostream& os, const Output_Options& oo ){
    std::string message_name = m_message ? m_message->get_name() : "";
    
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\brief Enum for Signal " << m_name_signal << (m_message ? ( " in Message " + message_name) : "") << std::endl;
        os << " */" << std::endl;
    }
    
    int max_name_length = 0;
    for( int i = 0; i < m_values.size(); i++ ){
        int length = message_name.length() + 1 + m_name_signal.length() + 1 + m_values[i].description.length();
        if( length > max_name_length){
            max_name_length = length;
        }
    }
    
    // TODO: Doppelte Values aussortieren, bzw. 001, 002, ... anhängen.

    std::map<std::string, int> duplicates;
    
    os << "typedef enum{" << std::endl;
    for( int i = 0; i < m_values.size(); i++ ){
        
        os << "   " << std::left << std::setfill (' ') << std::setw(max_name_length) 
                << to_upper_case(replace_invalid_C_characters( message_name + "_"  )) 
                 + to_upper_case(replace_invalid_C_characters( m_name_signal + "_" + m_values[i].description + (duplicates[m_values[i].description] == 0 ? "" : ("_"+std::to_string(duplicates[m_values[i].description])) ))) 
                << " = " << m_values[i].value << "," << std::endl;        
        
        duplicates[m_values[i].description]++;
    }
    os << "} ENUM_" << (m_message ? (m_message->get_name()+"_") : "") << m_name_signal << ";" << std::endl;
    os << std::endl;
}