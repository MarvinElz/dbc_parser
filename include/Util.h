/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Util.h
 * Author: Elz
 *
 * Created on 5. Januar 2022, 09:41
 */

#ifndef UTIL_H
#define UTIL_H

//#include <cstring>
#include <string>

#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef ABS
#define ABS(x) ((x)>=0?(x):(-(x)))
#endif

uint64_t calc_mask( int bitlength );

std::string replace_invalid_C_characters( const std::string& s );

//std::string to_upper_case( const std::string& s );

#endif /* UTIL_H */

