/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entry.h
 * Author: Elz
 *
 * Created on 4. Januar 2022, 15:47
 */

#ifndef ENTRY_H
#define ENTRY_H

#include <sstream>

typedef struct{
    std::string output_file;
    bool b_documentation;
    bool b_to_stdout;
} Output_Options;

typedef struct{
    std::string input_file;
    bool b_verbose;
} Parsing_Options;

class Entry{
    public :
        //virtual Entry* parse( std::stringstream& ss );
        virtual void print() = 0;
        virtual void output_c( std::ostream&, const Output_Options& ) = 0;
    
        const std::string& get_name() const { return m_name; };
    
    protected:
        std::string m_name;
    
};

#endif /* ENTRY_H */

