/*
 * DatumStack.cpp
 *
 * COMP 15 Project 2: CalcYouLater - Week 1 (Deliverable #2)
 * 
 * The implementation for the DatumStack class. The class uses 
 * a list of Datum elements from std::list and calls the appropriate
 * functions under that list class when the methods in DatumStack
 * are called. A print function is also included for testing purposes
 * 
 * Edited by Javier Laveaga (jlavea01) Saturday, October 14.
 */

#include "DatumStack.h"

/*
 * name: DatumStack  
 * purpose: to Initialize a DatumStack
 * arguments: None
 * returns: Nothing
 * effects: Initialize a DatumStack
 */
DatumStack::DatumStack() {
   
}

/*
 * name: DatumStack 
 * purpose: to create a stack initialized so that the elements of the array
 * are on the stack with the array's element 0 pushed on first
 * arguments: An array of Datum and an integer specifying the array size
 * returns: Nothing
 * effects: Creates an initialized DatumStack based on the array
 */
DatumStack::DatumStack(Datum arr[], int size) {
    for (int i = 0; i < size; i++) {
        this->push(arr[i]);
    }
}

/*
 * name: isEmpty  
 * purpose: to determine whether the stack is empty or not
 * arguments: none
 * returns: a boolean that is true if the stack is empty and false otherwise
 * effects: None
 */
bool DatumStack::isEmpty() {
    if (stack.size() == 0) {
        return true;
    } 
    return false;
}

/*
 * name: clear
 * purpose: to make the stack into an empty stack
 * arguments: None
 * returns: Nothing
 * effects: Erases all the elements of the stack, deallocating the memory
 * of each Datum element and decreasing the size to 0
 */
void DatumStack::clear() {
    if (not this->isEmpty()) {
        list<Datum>::iterator it1, it2;
        it1 = stack.begin();
        it2 = stack.end();
        stack.erase(it1, it2); // erases everything but last element
    }
}

/*
 * name: size  
 * purpose: to get the number of Datum elements on the stack
 * arguments: None
 * returns: an integer indicating the size of the DatumStack
 * effects: None
 */
int DatumStack::size() {
    return stack.size();
}

/*
 * name: push
 * purpose: To put the given datum element on the top of the stack 
 * arguments: A Datum object
 * returns: Nothing
 * effects: Adds one more element to the top of the stack, increasing size
 */
void DatumStack::push(Datum element) {
    stack.push_back(element);
}

/*
 * name: top 
 * purpose: to get the top Datum element of the stack 
 * arguments: None
 * returns: returns the top Datum element on the stack
 * effects: Throws runtime error if the stack is empty
 */
Datum DatumStack::top() {
    if (this->isEmpty()) {
        throw runtime_error("empty_stack"); 
    } 
    return stack.back();
}

/*
 * name: pop
 * purpose: to remove the top Datum element on the stack
 * arguments: None
 * returns: Nothing
 * effects: deallocates memory for the top element and throws a runtime
 * error if the stack is empty
 */
void DatumStack::pop() {
    if (this->isEmpty()) {
        throw runtime_error("empty_stack"); 
    } 
    stack.pop_back();
}

/*
 * name: print 
 * purpose: to add all the elements of the stack in string format 
 * to an output stream. (For testing purposes)
 * arguments: an output stream
 * returns: Nothing
 * effects: Adds the string of each Datum element to the output stream
 */
void DatumStack::print(ostream &output) {
    list<Datum>::iterator it;
    for (it = stack.begin(); it != stack.end(); it++) {
        //Dereference it to access current Datum
        output << it->toString();
    }
}




