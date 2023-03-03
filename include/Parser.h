/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: Elz
 *
 * Created on 4. Januar 2022, 17:52
 */

#ifndef PARSER_H
#define PARSER_H

#include <fstream>

class Parser{
    public:
        Parser(std::string filename);

        
    private:
        std::ifstream file;
    
    // TODO: Datei laden
    // Parsing
    
};


#endif /* PARSER_H */

