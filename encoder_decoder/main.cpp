/*
 * main.cpp
 * Javier Laveaga
 * 11/15/2023
 * 
 * CS 15 Project 3: Zap
 * 
 * Purpose: The main program of the HuffmanCoder class. It reads the
 * arguments and determines whether or not the appropriate commands
 * are being used. If not, it prints to cerr and exits the program.
 * Determines whether the user wants to zap or unzap a file and calls
 * the appropriate function: either encoder or decoder.
 * 
 */
#include "HuffmanCoder.h"

int main(int argc, char *argv[]) {
    HuffmanCoder program;
    string command = argv[1];
    if (argc != 4) {
        cerr << "Usage: " <<
        "./zap [zap | unzap] inputFile outputFile";
        cerr << endl;
        exit(EXIT_FAILURE);
    } else if (command == "zap") {
        program.encoder(argv[2], argv[3]);
    } else if (command == "unzap") {
        program.decoder(argv[2], argv[3]);
    } else {
        cerr << "Usage: " <<
        "./zap [zap | unzap] inputFile outputFile";
        cerr << endl;
        exit(EXIT_FAILURE);
    }  
}
