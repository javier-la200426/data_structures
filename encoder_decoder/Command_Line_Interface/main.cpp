/*
 * main.cpp
 * Javier Laveaga and Eva Caro
 * 12/10/2023
 * 
 * CS 15 Project 4: Gerp
 * 
 * Purpose: The main program of the Gerper class, which creates a 
 * word-search algorithm. It makes sure that the number of arguments
 * is equal to 3. It handles the case where the directory is an empty
 * directory and calls the appropriate functions based on that. It 
 * declares an output stream to be able to write to the provided 
 * output file, and checks to see if the output file can be opened.
 * 
 */
#include "Gerper.h"
using namespace std;

template<typename streamtype>
void check_open(streamtype &stream, string file_name);

/*
 * name:      main
 * purpose:   to check that the correct number of arguments is passed as 
 * well as to instantiate an object of the gerper class and call its
 * necessary members. It declares an output stream for the output file.
 * arguments: The number of arguments and the arguments themselves
 * returns:   An integer to end the program
 * effects:   prints to std out if number of arguments is not equal to 3
 */
int main(int argc, char *argv[]) {
    if (argc == 3) {
        Gerper program;
        bool empty_tree = program.save_files(argv[1]);
        if (not empty_tree) {
            program.read_files();
            ofstream outstream;
            check_open(outstream, argv[2]);
            program.read_query(outstream);
        }
    } else {
        cout << "Usage: ./gerp inputDirectory outputFile" << endl;
    }
    
}

/*
 * name: check_open
 * purpose: Checks to see if the input or output file can be opened
 * arguments: Either the commands file or the output file to be used
 * returns: Nothing 
 * effects: Will throw an error if there is an error opening the file
 */
template<typename streamtype>
void check_open(streamtype &stream, string file_name) {
        stream.open(file_name);
        if (not stream.is_open()) {
                cerr << "Error: could not open file " << file_name << endl;
                exit(EXIT_FAILURE);
        }
 }

