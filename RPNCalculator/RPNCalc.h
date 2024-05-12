/*
 * RPNCalc.h
 * Javier Laveaga
 * 10/22/2023
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * Purpose: Header file of RPNCalc. This defines the class. The RPNCalc 
 * class contains a stack to store Datum objects and performs several
 * operations on them. 
 * The run function asks for user input. The first six
 * methods are responsible for implementing simple commands such as printing,
 * or swapping. These functions are later grouped and called
 * by the simple_commands method, which is used in the run_loop. 
 * The method easy_commands calls push_datum to push datums into 
 * the stack when 'easy commands' like #f, #t, and an integer are inputted.
 * The method 'operation' groups together all the arithmetic operations 
 * and their executions. The method bool_operation groups together all the
 * inequalities and equality operations. The quit_or_operation method, 
 * used in the run_loop, later calls both the bool_operation and operation
 * methods. Separate methods were made to implement the exec, if, and file
 * commands. (More information describing the RPNCalc as a whole in 
 * the header file of RPNCalc.cpp)
 * 
 */

#ifndef RPNCALC_H
#define RPNCALC_H

#include "parser.h"
#include "DatumStack.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class RPNCalc {
    public:

    RPNCalc();
    ~RPNCalc();
    void run();

    private:
    void not_datum(string command);
    void print(string command);
    void clear(string command);
    void drop(string command);
    void dup(string command);
    void swap(string command);

    bool got_int(string s, int *resultp);
    void push_datum(Datum datum);

    void operation(string command);
    void bool_operation(string commmand);
   
    void run_loop(istream &input);

    void quit_or_operation (string command, bool *run);
    void exec(string command);
    void file(string command);
    void open_check(ifstream &intream, string file_name);
    void if_c(string command);
    void error_messages (bool runtime_error, string curr_c, string message);
    void simple_commands (string command);
    void easy_commands (string command, istream &input);
    void check_valid_command (string command);

    DatumStack stack; 
};


#endif