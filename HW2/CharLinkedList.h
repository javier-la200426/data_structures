/*
 *  CharLinkedList.h
 *  Javier Laveaga
 *  09/21/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Purpose : Header file of a character linked list. This defines the class.
 *  This linked list contains nodes that point to one another with 
 *  previous and next pointers, thus is is a doubly linked list. 
 *  These nodes contain the characters in the list. 
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

//Jav added
#include <string>
using namespace std;

//Jav added

class CharLinkedList {
    //
    public:
    //constructors
    CharLinkedList();
    CharLinkedList(char c);
    ~CharLinkedList();
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);
    //Assignment operator
    CharLinkedList &operator=(const CharLinkedList &other);

    //Getters
    int size() const;
    string toString() const;
    string toReverseString() const;
    char first() const;
    char last() const;
    char elementAt(int index) const;
    bool isEmpty() const;
    //Setters
    void pushAtFront(char c);
    void pushAtBack(char c);
    void clear();
    void insertAt(char c, int index);
    void insertInOrder(char c);
    //Removing/replacing/concatenating
    void popFromBack();
    void popFromFront();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharLinkedList *other);

    private:
    
    struct Node {
        char data;
        Node *next;
        Node *prev;
    };

    Node *front;
    int num_nodes; 

    //Helper functions
    void recycle_recursive (Node *curr);
    char elementAt_helper (Node *curr, int count, int index) const;
    Node* specified_node (Node *curr, int count, int index) const;

};

#endif
