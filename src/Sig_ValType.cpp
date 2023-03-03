/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sig_ValType.h"

#include <iomanip>
#include <limits.h>

#include <iostream>

Sig_ValType* Sig_ValType::parse(std::stringstream& ss, const Parsing_Options& po){
    char next_char;
    if( (next_char = ss.peek()) == '\n' || next_char == '\r' || next_char == -1 || next_char == 0 ){
        return NULL;
    }

    // Beispiel: SIG_VALTYPE_ 419 kalibriert : 1;
    
    std::string signal_name;
    unsigned int id;
    unsigned int type;
    std::string dummy;
    
    ss >> id;
    ss >> signal_name;
    ss >> dummy;
    ss >> type;
    ss.ignore( INT_MAX, ';');
    
    if( type != TYPE_IEEE_FLOAT && type != TYPE_IEEE_DOUBLE ){
        std::cerr << "Error: Unsupported type in Message (ID) " << id << " and Signal '" << signal_name << "'" << std::endl;
        return NULL;
    }
    
    Sig_ValType* new_sig_valtype = new Sig_ValType();
    new_sig_valtype->m_id = id;
    new_sig_valtype->m_signal_name = signal_name;
    new_sig_valtype->m_valtype = (ValType)type;
    
    if( po.b_verbose ){
        new_sig_valtype->print();
    }
    
    return new_sig_valtype;
}

void Sig_ValType::print(){
    std::cout << "ValType:"        << std::endl;
    std::cout << "   Type: "       << m_valtype << std::endl;
    std::cout << "   ID: "         << m_id << std::endl;
    std::cout << "   Signalname: " << m_signal_name << std::endl;
}

void Sig_ValType::output_c( std::ostream& os, const Output_Options& oo ){
    // Nichts tun
}