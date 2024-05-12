/*
 * parser.cpp
 *
 * COMP 15 Project 2: CalcYouLater 
 * 
 * The definition of the function parseString. This function
 * takes in the address to an input stream and returns 
 * an rstring with its appropriate specifications.
 * 
 * Edited by Javier Laveaga (jlavea01) Saturday, October 14.
 */

#include "parser.h"


/*
 * name: parseRString 
 * purpose: to read in from an input string until all curly braces are 
 * matched and then returning a string with the characters separated by 
 * single whitespaces.
 * arguments: An reference to an istream.
 * returns: Returns an rstring (std::string) containing a sequence of 
 * characters beggining and ending with curly braces.
 * effects: Adds the characters to the string to be returned.
 */
string parseRString(istream &input) {
    int count = 1; // 1 right brace
    string total = "{ ";
    string current_char;
    while(count != 0) {
        input >> current_char;
        total = total + current_char;
        if (current_char == "}") {
            count--;
        } else if (current_char == "{") {
            count++;
        }
        if(count != 0) {
            total = total + " ";
        }
    }
    return total;
}
