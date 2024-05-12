/*
 *  CharArrayList.cpp
 *  Javier Laveaga
 *  Friday September 15th, 2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  To implement the Array List class
 *
 */ 

#include "CharArrayList.h"
#include <sstream>

using namespace std;

//Default constructor
CharArrayList:: CharArrayList() {
    Capacity = 0;
    data = nullptr;
    Size = 0;
}

//Second constructor
CharArrayList:: CharArrayList(char c) {
    data = new char [1];
    data[0] = c;
    Capacity = 1;
    Size = 1; //right?

}

//Third constructor
CharArrayList::CharArrayList(char arr[], int size)  {
    data = new char [size];
    for (int i = 0; i < size; i++) { //copying elements over
        data[i] = arr[i];
    }
    Capacity = size;
    Size = size;
}

//Copy contructor. No need for this b/c this is a new object
CharArrayList::CharArrayList(const CharArrayList &other) {
    if (other.data != nullptr) { //if other is pointing to st, then dereference
        data = new char[other.Capacity]; //allocate memory to match cap of other
        //copy over elements
        for (int i = 0; i < other.Capacity; i++) {
            data[i] = other.data[i]; 
        }
        Capacity = other.Capacity;
        Size = other.Size;
    } else { //if it is the nullptr
        Capacity = 0;
        data = nullptr;
        Size = 0;
    }
}


//Destructor
CharArrayList::~CharArrayList() {
    delete[] data;
}

//Assignment operator 
CharArrayList &CharArrayList::operator=(const CharArrayList &other) { //positioning of &?
    //other is the rhs
    //important so that you don't delete both lhs and rhs (nothing to copy over)
    if (this == &other) { //if lhs = rhs then
        return *this; //return the lhs address
    }
    delete[] data; //HERE to recylgcly left hand side (not necessary) 
    //but good if lhs is an array list with 1 billion elements
    //same code as copy constructor
    if (other.data != nullptr) { //if other is pointing to st, then dereference
        data = new char[other.Capacity]; //allocate memory to match cap of other 
        //copy over elements
        for (int i = 0; i < other.Capacity; i++) {
            data[i] = other.data[i]; //causing problems 
        }
        Capacity = other.Capacity;
        Size = other.Size;
    } else { //if it is the nullptr
        Capacity = 0;
        data = nullptr;
        Size = 0;
    }
    return *this;

}

//Function that determines if object/list is empty 
bool CharArrayList::isEmpty() const {
    if (Size == 0) {
        return true;
    } else {
        return false;
    } 
}
//Function that makes the arraylist empty
void CharArrayList::clear() { //not sure
    delete [] data;
    Size = 0;
    Capacity = 0;
    data = nullptr;
}

//Function that gets the size of the arraylist
int CharArrayList::size() const {
    return Size;
}

//Function that returns the first character of the arraylist
char CharArrayList::first() const {
    if(this->isEmpty()) {
        throw runtime_error("cannot get first of empty ArrayList"); //is this good???? (throw??)
    } else {
        return data[0];
    }
}

//Function that returns the last character of the arraylist
char CharArrayList::last() const {
    if(this->isEmpty()) {
        throw runtime_error("cannot get last of empty ArrayList"); //is this good???? (throw??)
    } else {
        return data[Size-1];
    }
}

//Function that returns the element at the specified index
char CharArrayList::elementAt(int index) const {
    if (index < 0 or index >= this->size()) {
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + ")"); 
    } else {  //if index is in range
        return data[index];
    }
}

//Function that returns a string containing the characters of the 
// Character Array list
string CharArrayList::toString() const { //do I need std here?

    string name = "";
    for (int i = 0; i < this->size(); i++) {
        name = name + data[i];
    }
    string phrase = "[CharArrayList of size " + to_string(this->size()) + 
    " <<" + name + ">>]"; //no new line
    return phrase;
}

//Function that returns a string containing the characters of the
// character array list in reverse order
string CharArrayList::toReverseString() const {
    string name = "";
    for (int i = this->size() - 1; i >= 0 ; i--) {
        name = name + data[i];
    }
    string phrase = "[CharArrayList of size " + to_string(this->size()) + 
    " <<" + name + ">>]"; //no new line
    return phrase;
}

//Function that increases capacity by a reasonable amount
void CharArrayList::expand() {
    //Allocate new larger array on the heap
    char *new_data = new char[2 * Capacity + 2]; //+2 just in case Capacity is 0
    //Copy over elements to new array
    for (int i = 0; i < this->size(); i++) {
        new_data[i] = data[i];
    }
    //recycle old array
    delete[] data;
    data = new_data;
    Capacity = 2 * Capacity + 2;
}

//Function that inserts the new element at the end of the array list
void CharArrayList::pushAtBack(char c) {
    //If Capacity is greater than Size (all good)
    if (Capacity > Size) {
        data[Size] = c;
        Size++;
    } else { //if Capacity is equal to Size
        //
        expand(); //after expand, we have more space
        data[Size] = c;
        Size++;
    }

}

//Function that inserts new given element in front of the existing elements of the array.
void CharArrayList::pushAtFront(char c) {
    //If Size is greater than or equal to Capacity, then expand
    if (Size >= Capacity) {
        expand();
    }
    char *temp_data = new char[Capacity]; //temporary data (same size)
    temp_data[0] = c;
    for (int i = 0; i < this->size(); i++) { //is "this" redundant
        temp_data[i+1] = data[i]; //copy over elements starting at index 1.
    }
    delete [] data;
    data = temp_data;
    //delete [] temp_data; //no need to delete since temp_data 
    //is pointing to same thing as data
    Size++;   
}

void CharArrayList::insertAt(char c, int index) {
    //
    if (index < 0 or index > this->size()) { //> not >=
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + "]"); 
    } else {  //if index is in range
        //Checking for Capacity / Size 
        if (Size >= Capacity) {
            expand();
        }
        char *temp_data = new char[Capacity]; //temporary data (same size)
        //copy over elements before index
        for (int i = 0; i < index; i++) {
            temp_data[i] = data[i];
        }
        //insert new element at index
        temp_data[index] = c;
        Size++; 
        //copy over rest of elements
        for (int i = index + 1; i < this->size(); i++) {
            temp_data[i] = data[i-1]; //size of old data is 1 less than temp. 
            //every element after indez is also 1 less
        }
        delete [] data;
        data = temp_data;
    }

}

//Function that takes in an element and inserts it in the array list in ASCII order
void CharArrayList::insertInOrder(char c) {
    if (Size >= Capacity) {
            expand();
    }
    int current_char;
    for(int i = 0; i < this->size(); i++) {
        current_char = data[i];
        if (current_char > c) {
            insertAt(c, i);
            i = this->size() + 1; // to break out of the loop.
        }
    }
}

//Function that removes the first element from the array list.
void CharArrayList::popFromFront() {
    if (this->isEmpty()) {
        throw runtime_error("cannot pop from empty ArrayList"); 
    } else {
        //shift all elements except first to the left
        for (int i = 0; i < (this->size() -1); i++) {
            data[i] = data[i + 1];
        }
        Size--;
    }
}

//Function that removes the last element from the array list.
void CharArrayList::popFromBack() {
     if (this->isEmpty()) {
        throw runtime_error("cannot pop from empty ArrayList"); 
    } else {
        Size--; //Is this it for this?
    }
}

//Function that removes the element at the specified index
void CharArrayList::removeAt(int index) {
     if (index < 0 or index >= this->size()) {
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + ")"); 
    } else {  //if index is in range
        //shift all elements (except the elements to left of index & including index) to the left
        for (int i = index; i < (this->size() -1); i++) {
            data[i] = data[i + 1];
        }
        Size--;
    }
}

//Function that replaces the element at the specified index with the new element
void CharArrayList::replaceAt(char c, int index) {
    if (index < 0 or index >= this->size()) {
        //Am I allowed to use to_string??"????????????????" Yes
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + ")"); 
    } else {
        data[index] = c;
    }
}

//Function that adds a copy of the array list pointed to by the parameter value to the end
// of the array list the function was called from.
void CharArrayList::concatenate(CharArrayList *other) {
    //
    if (Size >= Capacity) {
        expand();
    }
    //Save the sizes so that they don't keep changing after
    // Size++
    int initial_size_this = this->size();
    int initial_size_other = other->size();
    for (int i = 0; i < initial_size_other; i++) { 
        data[initial_size_this + i] = other->data[i];
        //cout <<  data[this->size() + i];
        Size++;
        
        if (Size >= Capacity) { 
            expand(); 
        } 

    }
}

//Gets the capacity of the list
int CharArrayList::capacity() const {
    return Capacity;
}

