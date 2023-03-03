/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Val_Table.h
 * Author: Elz
 *
 * Created on 4. Januar 2022, 15:47
 */

#ifndef VAL_TABLE_H
#define VAL_TABLE_H

#include <vector>
#include <string>
#include "Entry.h"
#include "Message.h"


typedef struct{
    int value;
    std::string description;
} Value_Definition;

class Val_Table : public Entry{
    public: 
        static Val_Table* parse( std::stringstream&, const Parsing_Options& );
    
        void print();
        void output_c( std::ostream&, const Output_Options& );
        
        int  get_message_id(){ return m_id_message; };
        void set_message( const Message* message ){ m_message = message; };
        
    private:
        
        Val_Table( unsigned int id_message, std::string name_signal, std::vector<Value_Definition> values )
        : m_id_message(id_message),
          m_name_signal(name_signal),
          m_values(values){
            m_message = NULL;
        };
        
        std::vector<Value_Definition> m_values;
        
        unsigned int m_id_message;
        const Message* m_message;
        std::string m_name_signal;
};

#endif /* VAL_TABLE_H */

