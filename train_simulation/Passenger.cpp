/*
 * Passenger.cpp
 *
 * COMP 15 Project 1: Metrosim - Phase 1
 * 
 * Implementation of the passenger structure that implements its print
 * function. It just prints the information of the passenger.
 * 
 * Edited by Javier Laveaga (jlavea01) Friday, September 29.
 */

#include <iostream>
#include <string>
#include "Passenger.h"
using namespace std; 

/*
 * name: print     
 * purpose: Function that prints the passenger information to 
 * the output stream
 * arguments: The address to the output stream
 * returns: Nothing 
 * effects: Prints the passenger ID and the arrival and departure 
 * station numbers in the proper format.
 */
void Passenger::print(std::ostream &output)
{
        output << "[" + to_string(id) + ", " + to_string(from) 
        + "->" + to_string(to) + "]";
}
