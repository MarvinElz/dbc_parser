/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.h
 * Author: Elz
 *
 * Created on 4. Januar 2022, 15:47
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "Entry.h"
#include "Comment.h"
#include <vector>
#include <iostream>

class Signal;

class Message : public Entry{
    public: 
        static Message* parse( std::stringstream&, const Parsing_Options& );
    
        void print();
        void output_c( std::ostream&, const Output_Options& );
    
        int  get_dlc(){return m_dlc;};
        bool get_m_ext(){return m_ext;};
        int  get_id() const {return m_id;};
        const std::vector<Signal*>& get_signals(){return m_signals;};
        
        void set_comment( Comment* comment ){ m_comment = comment; };
    
    private:
        Comment* m_comment = NULL;
        int  m_dlc;
        bool m_ext;
        uint32_t  m_id;    
        std::vector<Signal*> m_signals;
    
};

#endif /* MESSAGE_H */

