/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: Elz
 *
 * Created on 7. Januar 2022, 10:07
 */

#include <stdlib.h>
#include <iostream>

#include <string.h>


#include "DBC_Parser_Test.h"

/*
 * Simple C++ Test Suite
 */

bool test1() {
    /*
     Message1:
	Gesamt: 0x03, 0x40, 0xCC, 0xD0, 0x33, 0x33, 0x33, 0x34
	Signal_8_Bit_Signed_M = 13;
	Signal_16_Bit_Signed_M = 3277;
	Signal_32_Bit_Signed_M = 214748365;     
     */
    
    const int8_t  Signal_8_Bit_Signed_M = 13;
    const int16_t Signal_16_Bit_Signed_M = 3277;
    const int32_t Signal_32_Bit_Signed_M = 214748365;
    
    uint8_t data[8] = {0b00111111, 0b11001111, 0xff, 0b11110011, 0xff, 0xff, 0xff, 0b11111100};
    
    SET_Message1_Signal_8_Bit_Signed_M( data, Signal_8_Bit_Signed_M );
    SET_Message1_Signal_16_Bit_Signed_M( data, Signal_16_Bit_Signed_M );
    SET_Message1_Signal_32_Bit_Signed_M( data, Signal_32_Bit_Signed_M );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0x03, 0x40, 0xCC, 0xD0, 0x33, 0x33, 0x33, 0x34};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_8_Bit_Signed_M  != GET_Message1_Signal_8_Bit_Signed_M( data_cmp ) ) return 0;
    if( Signal_16_Bit_Signed_M != GET_Message1_Signal_16_Bit_Signed_M( data_cmp ) ) return 0;
    if( Signal_32_Bit_Signed_M != GET_Message1_Signal_32_Bit_Signed_M( data_cmp ) ) return 0;
    
    return 1;
}

bool test2() {
    /*
    Message2:
	Gesamt: 0xF3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33
	Signal_64_Bit_Signed_M = -922337203685477581;     
     */
    
    const int64_t Signal_64_Bit_Signed_M = (int64_t)-922337203685477581;
    
    uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    SET_Message2_Signal_64_Bit_Signed_M( data, Signal_64_Bit_Signed_M );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " ";
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0xF3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_64_Bit_Signed_M != GET_Message2_Signal_64_Bit_Signed_M( data_cmp ) ) return 0;
    
    return 1;
}

bool test3() {
    /*
    Message3:
	Gesamt: 0x03, 0x40, 0xCC, 0xD0, 0x66, 0x66, 0x66, 0x68
	Signal_8_Bit_Unsigned_M = 13;
	Signal_16_Bit_Unsigned_M = 3277;
	Signal_32_Bit_Unsigned_M = 214748365;     
     */
    const uint8_t  Signal_8_Bit_Unsigned_M = 13;
    const uint16_t Signal_16_Bit_Unsigned_M = 3277;
    const uint32_t Signal_32_Bit_Unsigned_M = 214748365;
    
    uint8_t data[8] = {0b00111111, 0b11001111, 0xff, 0b11110111, 0xff, 0xff, 0xff, 0b1111000};
    
    SET_Message3_Signal_8_Bit_Unsigned_M ( data, Signal_8_Bit_Unsigned_M );
    SET_Message3_Signal_16_Bit_Unsigned_M( data, Signal_16_Bit_Unsigned_M );
    SET_Message3_Signal_32_Bit_Unsigned_M( data, Signal_32_Bit_Unsigned_M );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0x03, 0x40, 0xCC, 0xD0, 0x66, 0x66, 0x66, 0x68};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_8_Bit_Unsigned_M   != GET_Message3_Signal_8_Bit_Unsigned_M ( data_cmp ) ) return 0;
    if( Signal_16_Bit_Unsigned_M  != GET_Message3_Signal_16_Bit_Unsigned_M( data_cmp ) ) return 0;
    if( Signal_32_Bit_Unsigned_M  != GET_Message3_Signal_32_Bit_Unsigned_M( data_cmp ) ) return 0;
    
    return 1;
}

bool test4() {
    /*
    Message4:
	Gesamt: 0x0C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCD
	Signal_64_Bit_Unsigned_M = 922337203685477581;    
     */
    const uint64_t  Signal_64_Bit_Unsigned_M = 922337203685477581;
    
    uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    SET_Message4_Signal_64_Bit_Unsigned_M( data, Signal_64_Bit_Unsigned_M );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0x0C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCD};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_64_Bit_Unsigned_M   != GET_Message4_Signal_64_Bit_Unsigned_M ( data_cmp ) ) return 0;
    
    return 1;
}

bool test5() {
    /*
    Message5:
	Gesamt:	0x34, 0xD0, 0xCC, 0x40, 0x33, 0x33, 0x33, 0x03
	Signal_8_Bit_Signed_I = 13;
	Signal_16_Bit_Signed_I = 3277;
	Signal_32_Bit_Signed_I = 214748365;
     */
    const int8_t  Signal_8_Bit_Signed_I  = 13;
    const int16_t Signal_16_Bit_Signed_I = 3277;
    const int32_t Signal_32_Bit_Signed_I = 214748365;
    
    uint8_t data[8] = { 0b11111100, 0b11110011, 0xff, 0b11001111, 0xff, 0xff, 0xff, 0b00111111 };
    
    SET_Message5_Signal_8_Bit_Signed_I ( data, Signal_8_Bit_Signed_I );
    SET_Message5_Signal_16_Bit_Signed_I( data, Signal_16_Bit_Signed_I );
    SET_Message5_Signal_32_Bit_Signed_I( data, Signal_32_Bit_Signed_I );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0x34, 0xD0, 0xCC, 0x40, 0x33, 0x33, 0x33, 0x03};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_8_Bit_Signed_I  != GET_Message5_Signal_8_Bit_Signed_I ( data_cmp ) ) return 0;
    if( Signal_16_Bit_Signed_I != GET_Message5_Signal_16_Bit_Signed_I( data_cmp ) ) return 0;
    if( Signal_32_Bit_Signed_I != GET_Message5_Signal_32_Bit_Signed_I( data_cmp ) ) return 0;
    
    return 1;
}

bool test6() {
    /*
    Message6:
	Gesamt: 0xCD, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x0C
	Signal_64_Bit_Signed_I = 922337203685477581;
     */
    const int64_t  Signal_64_Bit_Signed_I = 922337203685477581;
    
    uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    SET_Message6_Signal_64_Bit_Signed_I ( data, Signal_64_Bit_Signed_I );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0xCD, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x0C};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_64_Bit_Signed_I  != GET_Message6_Signal_64_Bit_Signed_I ( data_cmp ) ) return 0;
    
    return 1;
}

bool test7() {
    /*
    Message7:
	Gesamt: 0x34, 0xD0, 0xCC; 0x40, 0x33, 0x33, 0x33, 0x03
	Signal_8_Bit_Unsigned_I = 13;
	Signal_16_Bit_Unsigned_I = 3277;
	Signal_32_Bit_Unsigned_I = 214748365;
     */
    const uint8_t  Signal_8_Bit_Unsigned_I  = 13;
    const uint16_t Signal_16_Bit_Unsigned_I = 3277;
    const uint32_t Signal_32_Bit_Unsigned_I = 214748365;
    
    uint8_t data[8] = { 0b11111100, 0b11110011, 0xff, 0b11001111, 0xff, 0xff, 0xff, 0b00111111 };
    
    SET_Message7_Signal_8_Bit_Unsigned_I ( data, Signal_8_Bit_Unsigned_I );
    SET_Message7_Signal_16_Bit_Unsigned_I( data, Signal_16_Bit_Unsigned_I );
    SET_Message7_Signal_32_Bit_Unsigned_I( data, Signal_32_Bit_Unsigned_I );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0x34, 0xD0, 0xCC, 0x40, 0x33, 0x33, 0x33, 0x03};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_8_Bit_Unsigned_I  != GET_Message7_Signal_8_Bit_Unsigned_I ( data_cmp ) ) return 0;
    if( Signal_16_Bit_Unsigned_I != GET_Message7_Signal_16_Bit_Unsigned_I( data_cmp ) ) return 0;
    if( Signal_32_Bit_Unsigned_I != GET_Message7_Signal_32_Bit_Unsigned_I( data_cmp ) ) return 0;
    
    return 1;
}

bool test8() {
    /*
    Message8:
	Gesamt: 0xCD, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x0C 
	Signal_64_Bit_Unsigned_I = 922337203685477581;
     */
    const uint64_t Signal_64_Bit_Unsigned_I = 922337203685477581;
    
    uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    SET_Message8_Signal_64_Bit_Unsigned_I( data, Signal_64_Bit_Unsigned_I );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0xCD, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x0C };
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_64_Bit_Unsigned_I  != GET_Message8_Signal_64_Bit_Unsigned_I ( data_cmp ) ) return 0;
    
    return 1;
}

bool test9() {
    /*
    Message9:
	Gesamt: 0x73, 0x28, 0xCC, 0x1C, 0x59, 0x90, 0xCF, 0x08
	Signal_12_Bit_Unsigned_M = 3685;
	Signal_12_Bit_Signed_I = -410;
	Signal_12_Bit_Signed_M = -1230;
	Signal_12_Bit_Unsigned_I = 2255;
     */
    
    const uint16_t Signal_12_Bit_Unsigned_M = 3685;
    const  int16_t Signal_12_Bit_Signed_I   = -410;
    const  int16_t Signal_12_Bit_Signed_M   = -1230;
    const uint16_t Signal_12_Bit_Unsigned_I = 2255;
    
    uint8_t data[8] = {0b01111111, 0b11111000, 0b11111110, 0b00011111, 0b01111111, 0b11111000, 0xff, 0b00001111};
    
    SET_Message9_Signal_12_Bit_Unsigned_M( data, Signal_12_Bit_Unsigned_M );
    SET_Message9_Signal_12_Bit_Signed_I  ( data, Signal_12_Bit_Signed_I );
    SET_Message9_Signal_12_Bit_Signed_M  ( data, Signal_12_Bit_Signed_M );
    SET_Message9_Signal_12_Bit_Unsigned_I( data, Signal_12_Bit_Unsigned_I );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " " << std::endl;
    }
    std::cout << std::endl;
    */
    
    const uint8_t data_cmp[] = {0x73, 0x28, 0xCC, 0x1C, 0x59, 0x90, 0xCF, 0x08};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    if( Signal_12_Bit_Unsigned_M != GET_Message9_Signal_12_Bit_Unsigned_M( data_cmp ) ) return 0;
    if( Signal_12_Bit_Signed_I   != GET_Message9_Signal_12_Bit_Signed_I  ( data_cmp ) ) return 0;
    if( Signal_12_Bit_Signed_M   != GET_Message9_Signal_12_Bit_Signed_M  ( data_cmp ) ) return 0;
    if( Signal_12_Bit_Unsigned_I != GET_Message9_Signal_12_Bit_Unsigned_I( data_cmp ) ) return 0;
    
    return 1;
}

bool test10() {
    /*
    Message10:
	Gesamt: 0x66, 0x0E, 0x5F, 0xF8, 0xA0, 0x19, 0x4C, 0xE0
	Signal_12_Bit_Signed_I_Factor = -31.0;
	Signal_12_Bit_Signed_M_Factor = -92.5;
	Signal_12_Bit_Unsigned_I_Factor = 92.0;
	Signal_12_Bit_Unsigned_M_Factor = 133.0;
     */
    
    const float Signal_12_Bit_Signed_I_Factor = -31.0;
    const float Signal_12_Bit_Signed_M_Factor = -92.5;
    const float Signal_12_Bit_Unsigned_I_Factor = 92.0;
    const float Signal_12_Bit_Unsigned_M_Factor = 133.0;
    
    uint8_t data[8] = {0xff, 0b00001111, 0b01111111, 0b11111000, 0b11111000, 0b01111111, 0xff, 0b11110000};
    
    SET_Message10_Signal_12_Bit_Signed_I_Factor  ( data, Signal_12_Bit_Signed_I_Factor );
    SET_Message10_Signal_12_Bit_Signed_M_Factor  ( data, Signal_12_Bit_Signed_M_Factor );    
    SET_Message10_Signal_12_Bit_Unsigned_I_Factor( data, Signal_12_Bit_Unsigned_I_Factor );
    SET_Message10_Signal_12_Bit_Unsigned_M_Factor( data, Signal_12_Bit_Unsigned_M_Factor );
    
    /*
    for( int i = 0; i < 8; i++ ){
        std::cout << std::hex << (int)data[i] << " ";
    }
    std::cout << std::endl;
     * */
    
    const uint8_t data_cmp[] = {0x66, 0x0E, 0x5F, 0xF8, 0xA0, 0x19, 0x4C, 0xE0};
    if( memcmp( data, data_cmp, 8 ) != 0 ) return 0;
    
    //std::cout << "GET_Message10_Signal_12_Bit_Signed_I_Factor  ( data_cmp ): " << GET_Message10_Signal_12_Bit_Signed_I_Factor  ( data_cmp ) << std::endl;
    //std::cout << "GET_Message10_Signal_12_Bit_Signed_M_Factor  ( data_cmp ): " << GET_Message10_Signal_12_Bit_Signed_M_Factor  ( data_cmp ) << std::endl;
    //std::cout << "GET_Message10_Signal_12_Bit_Unsigned_I_Factor( data_cmp ): " << GET_Message10_Signal_12_Bit_Unsigned_I_Factor( data_cmp ) << std::endl;
    //std::cout << "GET_Message10_Signal_12_Bit_Unsigned_M_Factor( data_cmp ): " << GET_Message10_Signal_12_Bit_Unsigned_M_Factor( data_cmp ) << std::endl;
    
    if( Signal_12_Bit_Signed_I_Factor   != (float)GET_Message10_Signal_12_Bit_Signed_I_Factor  ( data_cmp ) ) return 0;
    if( Signal_12_Bit_Signed_M_Factor   != (float)GET_Message10_Signal_12_Bit_Signed_M_Factor  ( data_cmp ) ) return 0;
    if( Signal_12_Bit_Unsigned_I_Factor != (float)GET_Message10_Signal_12_Bit_Unsigned_I_Factor( data_cmp ) ) return 0;
    if( Signal_12_Bit_Unsigned_M_Factor != (float)GET_Message10_Signal_12_Bit_Unsigned_M_Factor( data_cmp ) ) return 0;
    
    return 1;
}


int main(int argc, char** argv) {
    if( !test1() ){
        std::cerr << "test1 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test1 passed." << std::endl;
    }
    
    if( !test2() ){
        std::cerr << "test2 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test2 passed." << std::endl;
    }
    
    if( !test3() ){
        std::cerr << "test3 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test3 passed." << std::endl;
    }
    
    if( !test4() ){
        std::cerr << "test4 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test4 passed." << std::endl;
    }
    
    if( !test5() ){
        std::cerr << "test5 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test5 passed." << std::endl;
    }
    
    if( !test6() ){
        std::cerr << "test6 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test6 passed." << std::endl;
    }
    
    if( !test7() ){
        std::cerr << "test7 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test7 passed." << std::endl;
    }
    
    if( !test8() ){
        std::cerr << "test8 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test8 passed." << std::endl;
    }
    
    if( !test9() ){
        std::cerr << "test9 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test9 passed." << std::endl;
    }
    
    if( !test10() ){
        std::cerr << "test10 failed." << std::endl;
        return 1;
    }else{
        std::cout << "test10 passed." << std::endl;
    }
    
    std::cout << "All Tests passed!" << std::endl;

    return (EXIT_SUCCESS);
}

