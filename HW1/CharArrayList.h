/*
 *  CharArrayList.h
 *  Javier Laveaga
 *  Friday September 15th, 2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Header file of an array list. This defines the class. 
 *
 */
#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H

//Jav added
#include <string>

//Jav added

class CharArrayList {
    public:
    //Constructors
    CharArrayList (); //default
    CharArrayList(char c); //2nd 
    CharArrayList(char arr[], int size); //3rd
    CharArrayList(const CharArrayList &other); //Copy constructor

    //Destructor
    ~CharArrayList();
    //Assignment operator
    CharArrayList& operator=(const CharArrayList &other);

    //Methods

    bool isEmpty() const;//the const does not let you mess with variables
    void clear();

    //Getters
    int size() const;
    char first() const;
    char last() const;
    char elementAt(int index) const;
    std::string toString() const; //do I need std???yes u do. but why??
    std::string toReverseString() const;
    //Javier Getters
    int capacity() const;

    //Setters
    void pushAtBack(char c);
    void pushAtFront(char c);
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharArrayList *other);

    

    private:

    char *data; //create a getter for this
    int Size;
    int Capacity; //create a getter for this

    void expand();
};


#endif
