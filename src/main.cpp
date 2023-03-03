/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Elz
 *
 * Created on 4. Januar 2022, 14:41
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>

#include "Message.h"
#include "Signal.h"
#include "Val_Table.h"
#include "Comment.h"
#include "Sig_ValType.h"

#include "Util.h"
#include "Header.h"


std::vector<Message*>     messages;
std::vector<Signal*>      signals;
std::vector<Val_Table*>   val_tables;
std::vector<Comment*>     comments;
std::vector<Sig_ValType*> sig_valtypes;

void print_usage(){
    std::cout << "DBC-Parser converts DBC-Files to C-Code." << std::endl;
    std::cout << "Version 2.4" << std::endl;
    std::cout << "Supports both INTEL and MOTOROLA formats, not-8-bit-aligned values and both IEEE-formats (Float and Double)." << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "   dbc_parser2 [dbc_file.dbc] [h_file.h] [options]" << std::endl;
    std::cout << "   Options:" << std::endl;
    std::cout << "      -h | Output this help" << std::endl;
    std::cout << "      -v | verbose" << std::endl;
    std::cout << "      -d | without documentation (doxygen)" << std::endl;
}

// Fügt die Kommentare den jeweiligen Signalen/Nachrichten zu
void set_comments( ){
    for( int i = 0; i < comments.size(); i++ ){
        for( int j = 0; j < messages.size(); j++ ){
            if( messages[j]->get_id() == comments[i]->id() ){
                if( comments[i]->type().compare("SG_") == 0 ){        
                    const std::vector<Signal*> signals = messages[j]->get_signals();
                    for( int n = 0; n < signals.size(); n++ ){
                        if( signals[n]->get_name().compare( comments[i]->signal_name() ) == 0 ){
                            signals[n]->set_comment( comments[i] );
                        }
                    }
                }else if( comments[i]->type().compare("BO_") == 0 ){
                    messages[j]->set_comment( comments[i] );
                }
            }
        }
    }
}

// Fügt die ValTypes den jeweiligen Signal/Nachrichtn hinzu
void set_valtypes(){
    for( int i = 0; i < sig_valtypes.size(); i++ ){
        for( int j = 0; j < messages.size(); j++ ){
            if( messages[j]->get_id() == sig_valtypes[i]->id() ){
                const std::vector<Signal*> signals = messages[j]->get_signals();
                for( int n = 0; n < signals.size(); n++ ){
                    if( signals[n]->get_name().compare( sig_valtypes[i]->signal_name() ) == 0 ){
                        signals[n]->set_valtype( sig_valtypes[i] );
                    }
                }
            }
        }
    }
}

void parse( std::stringstream& ss, const Parsing_Options& po  ){
    std::string token;
    ss >> token;
    
    while( !ss.eof() ){
        if( token.empty() ) continue;
        
        if( token.compare(0, 14, "BA_DEF_SGTYPE_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0, 16, "SIGTYPE_VALTYPE_") == 0 ){
            // Nichts tun!        
        }else if( token.compare(0, 15, "BA_DEF_DEF_REL_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0, 13, "SIG_TYPE_REF_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0, 12, "SIG_VALTYPE_") == 0 ){
            Sig_ValType* new_sig_valtype = Sig_ValType::parse(ss, po);
            if( new_sig_valtype != NULL ){
                sig_valtypes.push_back( new_sig_valtype );
            }
        }else if( token.compare(0, 12, "ENVVAR_DATA_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0, 11, "SGTYPE_VAL_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0, 11, "BA_DEF_DEF_") == 0 ){
            ss.ignore( INT_MAX, '\n');            
        }else if( token.compare(0, 11, "BA_DEF_REL_") == 0 ){
            ss.ignore( INT_MAX, '\n'); 
        }else if( token.compare(0, 11, "SG_MUL_VAL_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0, 10, "VAL_TABLE_") == 0 ){
            ss.ignore( INT_MAX, '\n');
        }else if( token.compare(0, 10, "SIG_GROUP_") == 0 ){
            // Nichts tun!        
        }else if( token.compare(0, 10, "BA_SGTYPE_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0, 10, "BU_SG_REL_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0, 10, "BU_EV_REL_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0, 10, "BU_BO_REL_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0,  9, "BO_TX_BU_") == 0 ){
            // Nichts tun! 
        }else if( token.compare(0,  8, "NS_DESC_") == 0 ){
            // Nichts tun!
        }else if( token.compare(0,  8, "CAT_DEF_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  8, "EV_DATA_") == 0 ){
	    // Nichts tun!	
        }else if( token.compare(0,  7, "SGTYPE_") == 0 ){
	    // Nichts tun!        
        }else if( token.compare(0,  7, "VERSION") == 0 ){
	    ss.ignore( INT_MAX, '\n');
        }else if( token.compare(0,  7, "BA_REL_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  7, "BA_DEF_") == 0 ){
            ss.ignore( INT_MAX, '\n');	    
        }else if( token.compare(0,  6, "FILTER") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  4, "CAT_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  3, "BA_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  3, "NS_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  3, "BS_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  3, "BU_") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  3, "BA_") == 0 ){
	    ss.ignore( INT_MAX, '\n');
        }else if( token.compare(0,  1, ":") == 0 ){
	    // Nichts tun!
        }else if( token.compare(0,  3, "SG_") == 0 ){
            // Parse Signal
            Signal* new_signal = Signal::parse(ss, po);
            if( new_signal != NULL ){
                signals.push_back( new_signal );
            }
        }else if( token.compare(0, 3, "BO_") == 0 ){
            Message* new_message = Message::parse(ss, po);
            if( new_message != NULL ){
                messages.push_back( new_message );
            }
        }else if( token.compare(0, 4, "VAL_") == 0 ){
            Val_Table* new_val_table = Val_Table::parse(ss, po);
            if( new_val_table != NULL ){
                val_tables.push_back( new_val_table );
            }
        }else if( token.compare(0, 3, "CM_") == 0 ){
            Comment* new_comment = Comment::parse(ss, po);
            if( new_comment != NULL ){
                comments.push_back( new_comment );
            }
        }else{
            std::cout << "Token " << token << " not yet supported" << std::endl;
            ss.ignore( INT_MAX, '\n');
            //ss.getline( line, sizeof(line), '\n' );
        }
        ss >> token;
        //std::cout << "next token: " << token << std::endl;
    }
    
    for( int i = 0; i < val_tables.size(); i++ ){
        for( int j = 0; j < messages.size(); j++ ){
            if( val_tables[i]->get_message_id() == messages[j]->get_id() ){
                val_tables[i]->set_message( messages[j] );
            }
        }
    }
    
    //
    set_comments();
    set_valtypes();
    
    if(po.b_verbose){
        std::cout << "Parsing completed." << std::endl;
        std::cout << messages.size() << " messages parsed." << std::endl;
    }
}

static std::string get_extension(std::string fullpath){
    std::string::size_type const p(fullpath.find_last_of('.'));
    return fullpath.substr(p+1);
}

static std::string get_filename(std::string fullpath){
    // get filename
    std::string base_filename = fullpath.substr(fullpath.find_last_of("/\\") + 1);

    // remove extension from filename
    std::string::size_type const p(base_filename.find_last_of('.'));
    std::string file_without_extension = base_filename.substr(0, p);
    
    return file_without_extension;
}

bool handle_args( int argc, char** argv, Output_Options* oo, Parsing_Options* po){
    for(int i = 1; i < argc; i++){
        if( argv[i][0] == '-' ){
            switch( argv[i][1] ){
                case 'v': po->b_verbose = true; break;
                case 'd': oo->b_documentation = false;
                case 'h': return false;
                default:
                    std::cerr << "Could not read input parameter: " << argv[i] << std::endl;
                    break;
            }
            continue;
        }
        std::string extension = get_extension(std::string(argv[i]));
        std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c){ return std::tolower(c); });
        if( extension.compare("dbc") == 0 ){
            po->input_file = std::string(argv[i]);
            continue;
        }
        
        if( extension.compare("hpp") == 0 || extension.compare("h") == 0 ){
            oo->output_file = std::string(argv[i]);
            continue;
        }
        
        std::cerr << "Could not read input parameter: " << argv[i] << std::endl;        
    }
    return true;
}

/*
 * 
 */
int main(int argc, char** argv) {
    Output_Options oo = {
        .output_file = "",
        .b_documentation = true,
        .b_to_stdout = false,        
    };
    Parsing_Options po = {
        .input_file = "",
        .b_verbose = false,        
    };
    
    if( !handle_args( argc, argv, &oo, &po) ){
        print_usage();
        return 0;
    }
    
    if( po.input_file.empty() ){
        std::cerr << "You must provide at least the dbc-file" << std::endl;
        print_usage();
        return 1;
    }
    if( oo.output_file.empty() ){
        std::cout << "No output-file provided. Output to stdout." << std::endl;
        oo.b_to_stdout = true;
    }
    
    std::ifstream input_file;
    input_file.open( po.input_file );
    
    std::stringstream ss;
    if( input_file ){
        ss << input_file.rdbuf();
        input_file.close();
    }else{
        std::cerr << "Could not open input file: " << po.input_file << std::endl;
        return -1; 
    }
    
    parse( ss, po );
    
    std::ofstream output_file;
    if( !oo.b_to_stdout ){
        output_file.open( oo.output_file, std::ios::trunc );
    
        if( !output_file ){
            std::cerr << "Could not open output file: " << oo.output_file << std::endl;
            return -1;            
        }
    }
    
    std::ostream& os = output_file.is_open() ? output_file : std::cout;
    
    std::string filename = get_filename( po.input_file );
    std::transform(filename.begin(), filename.end(),filename.begin(), ::toupper);
    
    os << "#ifndef AUTO_" << std::uppercase << replace_invalid_C_characters(filename) << "_H" << std::endl;
    os << "#define AUTO_" << std::uppercase << replace_invalid_C_characters(filename) << "_H" << std::endl;
    
    os << "/****************************************************" << std::endl;
    os << "********* AUTOCODE GENERATED BY dbc_parser2 *********" << std::endl;
    os << "*********           DO NOT CHANGE           *********" << std::endl;
    os << "****************************************************/" << std::endl;    
    os << std::endl;
    
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\page page " << filename << std::endl;
        os << " */" << std::endl;
    }
    
    for( int i = 0; i < messages.size(); i++ ){
        messages[i]->output_c( os, oo );
    }    
    os << std::endl;
    
    if( oo.b_documentation ){
        os << "/**" << std::endl;
        os << " * \\section Value-Tables (converted to enums)" << std::endl;
        os << " */" << std::endl;
    }
    for( int i = 0; i < val_tables.size(); i++ ){
        val_tables[i]->output_c( os, oo );
        os << std::endl;
    }
    
    os << "#endif //AUTO_" << std::uppercase << filename << "_H" << std::endl;
    
    if( output_file ){
        output_file.close();
    }
    
    std::cout << "Conversion done." << std::endl;
    
    return 0;
}

