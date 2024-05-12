/*
 * main.cpp
 * Javier Laveaga
 * 10/22/2023
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * Purpose: The main program for the CalcYouLater class. It creates an instance
 * of the RPNCalc class and calls its run function. This function then  
 * asks for user input and calls the rest of the functions that maintain the 
 * Calculator.
 */

#include "RPNCalc.h"
#include "parser.h"


int main() {
    RPNCalc calculator;
    calculator.run();
    return 0;
}
