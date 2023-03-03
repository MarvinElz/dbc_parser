/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sig_ValType.h
 * Author: Elz
 *
 * Created on 1. Dezember 2022, 12:06
 */

#ifndef SIG_VALTYPE_H
#define SIG_VALTYPE_H

#include "Entry.h"

class Sig_ValType : public Entry{
    public: 
        typedef enum{
            TYPE_IEEE_FLOAT = 1,
            TYPE_IEEE_DOUBLE = 2
            // evtl. unvollständig
        } ValType;
        
        static Sig_ValType* parse( std::stringstream&, const Parsing_Options& );
        
        const ValType type(){ return m_valtype;};
        const unsigned int id(){ return m_id;};
        const std::string& signal_name(){ return m_signal_name; };
        void print();
        void output_c( std::ostream&, const Output_Options& );
        
    private:
        unsigned int m_id;          // Id der Nachricht
        std::string  m_signal_name; // Signalname
        ValType      m_valtype;
};

#endif /* SIG_VALTYPE_H */

