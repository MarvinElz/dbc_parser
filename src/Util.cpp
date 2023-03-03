/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Util.h"
#include <iostream>

uint64_t calc_mask( int bitlength ){
    if( bitlength == 64 ) return 0xFFFFFFFFFFFFFFFF;
    return ((uint64_t)1 << bitlength)-1;
}

std::string replace_invalid_C_characters( const std::string& s ){
    std::string valid_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
    std::string output( s );
    for( int i = 0; i < output.length(); i++ ){
        if( valid_characters.find( std::string(1,output[i]) ) == std::string::npos ){
            output[i] = '_';
        }
    }
    return output;
}

/*
std::string to_upper_case( const std::string& s ){
    std::string result;
    result.reserve( s.length() );
    for( int i = 0; i < s.length(); i++ ){
        result[i] = std::toupper(s[i]);
    }
    return result;
}
*/