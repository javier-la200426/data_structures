/*
 * DatumStack.h
 * 
 * COMP 15 Project 2: CalcYouLater - Week 1 (Deliverable #2)
 * 
 * The interface for a DatumStack. It holds a list of Datum 
 * objects, which represents the stack. It allows for the 
 * manipulation of the stack. This is done, for example, by
 * popping and pushing elements at the top of the stack, and
 * accessing the top element as well as its size.
 * 
 * Edited by Javier Laveaga (jlavea01) Saturday, October 14.
 * (if exec an rstring, use exec in if) Do exec first
 * 
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include "Datum.h"
#include <list>
#include <iostream> 
using namespace std;

class DatumStack {
    public:
    //Constructors
    DatumStack();
    DatumStack(Datum arr[], int size);
    //Getters
    bool isEmpty();
    int size();
    Datum top();
    //Setters
    void clear();
    void pop();
    void push(Datum element);
    
    private:
    void print(ostream &output); 
    list<Datum> stack;

};

#endif