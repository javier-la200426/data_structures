/*
 * main.cpp
 * Javier Laveaga
 * 10/6/2023
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * Purpose: The main program for the metrosim class. It reads in the number
 * of arguments, checks to see if the provided files can be opened, and
 * and initializes and then passes different streams to the metrosim functions
 * based on the number of arguments. Contains an opening function usinga a
 * template that checks if the file can be opened.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

//Function declarations
template<typename streamtype>
void check_open(streamtype &stream, string file_name);

int main(int argc, char *argv[]) {

        MetroSim program;
        ofstream outstream; //stream to write output to
        ifstream infile;
        if (argc < 3 or argc > 4) {
                cerr << "Usage: " <<
                "./MetroSim stationsFile outputFile [commandsFile]";
                cerr << endl;
                exit(EXIT_FAILURE);
        } else if (argc == 3) {
                //proceed w/out commands file (aka normally) with cin
                check_open(outstream, argv[2]);
                program.run_program(argv[1], cin, outstream);
        } else if (argc == 4) {
                //proceed w/ comands file.
                check_open(infile, argv[3]);
                check_open(outstream, argv[2]);
                program.run_program(argv[1], infile, outstream);
        }
        outstream.close();
        infile.close();
        return 0;
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
