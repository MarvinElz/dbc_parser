/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Comment.h
 * Author: Elz
 *
 * Created on 4. Januar 2022, 15:47
 */

#ifndef COMMENT_H
#define COMMENT_H

#include "Entry.h"
//#include <string>

class Comment : public Entry{
    public: 
        static Comment* parse( std::stringstream&, const Parsing_Options& );
        
        void print();
        void output_c( std::ostream&, const Output_Options& );
        const std::string& type(){ return m_type;};
        int id(){return m_id;};
        const std::string& signal_name(){return m_signal_name;};
        
    private:
        std::string m_text;
        std::string m_type;
        unsigned int m_id;
        std::string m_signal_name;
};

#endif /* COMMENT_H */

