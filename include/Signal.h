
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Signal.h
 * Author: Elz
 *
 * Created on 4. Januar 2022, 15:47
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include "Entry.h"
#include "Message.h"
#include "Comment.h"
#include "Sig_ValType.h"

typedef enum{
    MOTOROLA,
    INTEL
} Endianess;

typedef enum{
    UNSIGNED,
    SIGNED
} Signess;

class Signal : public Entry{
    public:
        static Signal* parse( std::stringstream&, const Parsing_Options& );

        void print();
        void output_c( std::ostream& os, const Output_Options& oo );
        
        void set_parent( Message* parent ){m_parent = parent;};
        
        void set_comment( Comment* comment ){ m_comment = comment; };
        void set_valtype( Sig_ValType* valtype ){ m_valtype = valtype; };
        
    private:
        Message* m_parent;
        Comment* m_comment = NULL;
        Sig_ValType* m_valtype = NULL;
        int m_length_bit;
        Endianess m_endianess;
        Signess m_signess;
        int m_startbit;
        std::string m_unit;
        float m_factor;
        float m_offset;
        float m_min;
        float m_max;     
        
        void set_intel( std::ostream& os, const Output_Options& oo );
        void get_intel( std::ostream& os, const Output_Options& oo );
        
        void set_motorola( std::ostream& os, const Output_Options& oo );
        void get_motorola( std::ostream& os, const Output_Options& oo );
        
        std::string datatype();
        int         datatype_length();
};

#endif /* SIGNAL_H */

