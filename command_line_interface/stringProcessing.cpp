/*
 * stringProcessing.cpp
 *
 * COMP 15 Project 4: Gerp 
 * 
 * The definition of the function stripNonAlphaNum. This function parses
 * through a string, getting rid of the non alphanumeric characters at 
 * the front and back.
 * 
 * Edited by Javier Laveaga (jlavea01) and Eva Caro (ecaro01) 
 * Saturday, Dec 2 2023
 */

#include "stringProcessing.h"

/*
 * name: stripNonAlphaNum
 * purpose: To remove all leading and trailing non-alphanumeric characters 
 * from the given string
 * arguments: A string to parse
 * returns: a string whose first and last characters are alphanumeric chars
 * effects: Nothing
 */
string stripNonAlphaNum (std::string input) {
    //if not non alpha numeric characters are found, return the empty string 
        while (input.length() != 0 and not isalpha(input[0]) 
            and not isdigit(input[0])) {
            //if length is 1, then turn non alpha to empty string
            if (input.length() == 1) {
                input = ""; 
            } else {
                //take one char off the front
                input = input.substr(1, input.length() - 1); 
            }
        }
        while (input.length() != 0 and not isalpha(input[input.length() - 1])
                and not isdigit(input[input.length() - 1])) {
            //take one char off the back
            input = input.substr(0, input.length() - 1);
        }
    return input;
}