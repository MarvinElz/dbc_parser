/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Comment.h"

#include <iomanip>
#include <limits.h>

#include "Util.h"

#include <iostream>

Comment* Comment::parse( std::stringstream& ss, const Parsing_Options& po){
    char next_char;
    if( (next_char = ss.peek()) == '\n' || next_char == '\r' || next_char == -1 || next_char == 0 ){
        return NULL;
    }

    std::string type;
    unsigned int id;
    
    ss >> type;    
    ss >> id;
    
    Comment* new_comment = new Comment();
    new_comment->m_type = type;
    new_comment->m_id = id & calc_mask(29);
    
    if( type.compare("SG_") == 0 ){        
        ss >> new_comment->m_signal_name;
    }else if( type.compare("BO_") == 0 ){
        // Nichts tun
    }else{
        std::cout << "Could not parse comment " << type << "." << std::endl;
        ss.ignore( INT_MAX, ';');
        delete new_comment;
        return NULL;
    }

    ss >> std::quoted(new_comment->m_text);
    ss.ignore( INT_MAX, ';');
    
    if( po.b_verbose ){
        new_comment->print();
    }
    
    return new_comment;
}
        
void Comment::print(){
    std::cout << "Comment:" << std::endl;
    std::cout << "   Type: " << m_type << std::endl;
    std::cout << "   ID: " << m_id << std::endl;
    std::cout << "   Text: " << m_text << std::endl;
}

void Comment::output_c( std::ostream& os, const Output_Options& oo ){
    os << "/********************* COMMENT **********************" << std::endl;
    os << m_text << std::endl;
    os << "****************************************************/" << std::endl;
}