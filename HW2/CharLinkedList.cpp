/*
 *  CharLinkedList.cpp
 *  Javier Laveaga
 *  09/21/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Purpose: To implement the Character Linked List class. This implementation 
 *  uses functions that can add, remove, or replace 
 *  elements in the list. Helper functions used recursion to iterate through
 *  the nodes in the list. 
 *
 */

#include "CharLinkedList.h"
#include <sstream>

using namespace std;


/*
 * name:      default constructor
 * purpose:   Initialize an empty linked list
 * arguments: None
 * returns:   Nothing
 * effects:  Creates an instancce of the CharLinkedList 
 */
CharLinkedList::CharLinkedList() {
    num_nodes = 0;
    front = nullptr;
}

/*
 * name: constructor (2)   
 * purpose: Creates a one element list consisting of that character 
 * arguments: a character to be added to the list
 * returns: Nothing  
 * effects: Creates an instancce of the CharLinkedList 
 */
CharLinkedList::CharLinkedList(char c) {
    //create a node or add node
    front = nullptr;
    num_nodes = 0;
    this->pushAtFront(c);
}

/*
 * name:      constructor (3)
 * purpose:   Initializes a linked list containing the characters in the array
 * arguments: None
 * returns:   Nothing
 * effects:  Creates an instancce of the CharLinkedList 
 */
CharLinkedList:: CharLinkedList(char arr[], int size) {
    front = nullptr;
    num_nodes = 0;
    for (int i = size - 1; i >= 0; i--) {
        pushAtFront(arr[i]); //this increments size 
    }
}

/*
 * name:      Destructor
 * purpose:   To delete the memory allocated for the nodes in the list
 * arguments: None
 * returns:   Nothing
 * effects:  Deletes the nodes in a list 
 */
CharLinkedList::~CharLinkedList() {
    recycle_recursive(front);
    //front = nullptr; //so that it doesnt point to st that was deleted.
}

//copy constructor
/*
 * name: CharLinkedList    
 * purpose: To create a CharLinkedList from another list
 * arguments: a CharLinkedList object
 * returns: A new object
 * effects: None
 */
CharLinkedList::CharLinkedList (const CharLinkedList &other) {
    //other is the one that aleady exists
    num_nodes = 0;
    front = nullptr;
    if (other.front != nullptr) { //if other is pointing to st
        //allocate memory for each node in list. copy over each node in other
        Node *curr = other.front;
        while (curr != nullptr) {
            this->pushAtBack(curr->data);
            curr = curr->next;
        }
        //curr is now is the nullptr (next last node)
    } else { 
        //if other is the null pointer & u are trying to 
        //make a copy of i (empty)
        num_nodes = 0;
        front = nullptr;
    }
}

//Assignment operator
/*
 * name: operator=     
 * purpose: To create a copy of a CharLinkedList object
 * arguments: a CharLinkedList object
 * returns: the address to the new CharLinkedList object
 * effects: None
 */
CharLinkedList& CharLinkedList::operator=(const CharLinkedList &other) {
    //other is rhs
    if (this == &other) { //if lhs and rhs are the same object
        return *this; //return the lhs address
    }
    //recylcle the lhs 
    this->recycle_recursive(front);

    //copy over each node
    num_nodes = 0;
    front = nullptr;
    if (other.front != nullptr) { //if other is pointing to st
        //allocate memory for each node in list. copy over each node in other
        Node *curr = other.front;
        while (curr != nullptr) {
            this->pushAtBack(curr->data);
            curr = curr->next;
        }
        //curr is now is the nullptr (next last node)
    } else { //if other is the null pointer & u are trying to make a
    // copy of i (empty)
        num_nodes = 0;
        front = nullptr;
    }
    return *this;
}

/*
 * name: recycle_recursive     
 * purpose: Helper function for destructor that deletes all nodes in a list
 * arguments: a pointer to a node, most often the front pointer
 * returns: Nothing. 
 * effects: Deletes elements of list
 */
void CharLinkedList::recycle_recursive (Node *curr) {
    if (curr == nullptr) {
        return;
    } else {
        recycle_recursive(curr->next);
        delete curr;
    }
}

/*
 * name: isEmpty     
 * purpose: Determines if the list is empty
 * arguments: Nonde
 * returns: a boolean indicating if the list is empty. If empty, it 
 * returns true. 
 * effects: None
 */
bool CharLinkedList::isEmpty() const {
   return (front == nullptr);
}

//Takes in an element and inserts it infront all other elements
/*
 * name: pushAtFront     
 * purpose: Takes in an element and inserts it infront all other elements
 * arguments: a character to be inserted in the list 
 * returns: Nothing.
 * effects: allocates new memory for the new node and moves around
 * pointers to put the new element into place.
 */
void CharLinkedList::pushAtFront(char c) {
    Node *new_node = new Node;
    if (front == nullptr) { //if empty
        front = new_node;
        new_node->prev = nullptr;
        new_node->next = nullptr;
        new_node->data = c;
    } else {
       // Node old_front = *front; //because front is a pointer. So dereference
        // to access node that it points to 
        //make what used to be 0th element point to new node
        front->prev = new_node; //new node is a node already. so just get
        //its address
        //new node next point to what front used to point to
        new_node->next = front;
        front = new_node;
        front->prev = nullptr; //w/out this line, u cause problems
        //because preveisu of front is unititialized
        new_node->data = c;
    }
    num_nodes++;
}

/*
 * name: pushAtBack     
 * purpose: Inserts a new element at the back of all elements.
 * arguments: A character to be inserted in the list. 
 * returns: Nothing
 * effects: allocates new memory for node and moves around
 * pointers to put the new element into place.
 */
void CharLinkedList::pushAtBack(char c) {
    Node *new_node = new Node;
    
    if (this->isEmpty()) { //if empty
        front = new_node;
        new_node->prev = nullptr;
        new_node->next = nullptr;
        new_node->data = c;
    } else {
        //if list is not empty
        Node *curr = front;
        while(curr->next != nullptr) {
            curr = curr->next;
        }
        //cur is now the last ode
        curr->next = new_node;
        new_node->prev = curr;
        new_node->next = nullptr;
        new_node->data = c;
    }
    num_nodes++;
}

/*
 * name: size    
 * purpose: Get the size of a list
 * arguments: None
 * returns: An integer indicating the size of the list
 * effects: None.
 */
int CharLinkedList::size() const {
    return num_nodes;
}

/*
 * name: toString    
 * purpose: Converts the characters of the list into a string
 * arguments: None
 * returns: a string representation of the list.
 * effects: None
 */
string CharLinkedList::toString() const {
    string name = "";
    if (this->isEmpty()) {
        name = "";
    } else {
        Node *curr = front;
        while (curr != nullptr) {
            name = name + curr->data;
            curr = curr->next;
        }
    }
    string message = "[CharLinkedList of size " + 
    to_string(this->size()) + " <<" + name + ">>]";
    return message;
}

//Converts the characters of the list into a string but in the reverse order
/*
 * name: toReverseString    
 * purpose: Converts the characters of the list into a string 
 * but in the reverse order
 * arguments: None
 * returns: a string representation of the list in the reverse order
 * effects: None.
 */
string CharLinkedList::toReverseString() const {

    string name = "";
    if (this->isEmpty()) {
        name = "";
    } else {
        Node *curr = front;
        int count = 0;
        int index = num_nodes - 1;

        Node* last_node = specified_node (curr, count, index);
        curr = last_node;
        //curr is now the last node ->true

        //now go from last to front using previous
        while (curr != nullptr) {
            //cout << "1" <<endl;
            name = name + curr->data;
            curr = curr->prev;
        }    
    }
    string message = "[CharLinkedList of size " 
    + to_string(this->size()) + " <<" + name + ">>]";
    return message;
}

/*
 * name: first     
 * purpose: Returns the first character in the list
 * arguments: None
 * returns: A character which is the first character in the list
 * effects: None
 */
char CharLinkedList::first() const {
    if (this->isEmpty()) {
        throw runtime_error("cannot get first of empty LinkedList"); 
    } else {
        return front->data;
    }
}

/*
 * name: last     
 * purpose: Gives the last element in the list
 * arguments: None
 * returns: Returns the last character in the list
 * effects: None 
 */
char CharLinkedList::last() const {

    if (this->isEmpty()) {
        throw runtime_error("cannot get last of empty LinkedList");            
    } else {
        Node *curr = front;
        while(curr->next != nullptr) {
            curr = curr->next;
        }
        //curr is now last node
        return curr->data;
    }
}

/*
 * name: clear     
 * purpose: Clears nodes in the list
 * arguments: None
 * returns: Nothing
 * effects: recycles the memory of a list
 */
void CharLinkedList::clear() {
    //delete all nodes
    this->recycle_recursive(front);
    front = nullptr; //so that when desctructor is called, it knows
    //list is empty
    num_nodes = 0;
}

/*
 * name: elementAt   
 * purpose: Returns the element at a given index
 * arguments: an index indicating the position of an element in the list
 * returns: a character representing the element at the index
 * effects: Gives an error if the index is out of range.
 */
char CharLinkedList::elementAt(int index) const {
    //if outside of range 
    if (index < 0 or index >= num_nodes ) {
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + ")"); 
    } else {
        int count = 0;
        Node *curr = front;
        char element =  elementAt_helper(curr, count, index);
        return element;
    }
    return ' '; 
}

/*
 * name: elementAt_helper     
 * purpose: Recursive function that returns the character at the
 * specified index
 * arguments: a pointer to a node (the front pointer), a count initialized 
 * to 0, and the desired index. 
 * returns: the character at the specified index.
 * effects: None
 */
char CharLinkedList:: elementAt_helper (Node *curr, int count, int index) 
                                        const {
    if (count == index) {
        return curr->data;
    }
    return elementAt_helper(curr->next, count + 1, index);
}

/*
 * name: specified_node     
 * purpose: Recursive function that returns the node at the specified index
 * arguments: a pointer to a node (the front pointer), a count initialized 
 * to 0, and the desired index. 
 * returns: the node at the specified index
 * effects: None
 */
CharLinkedList:: Node* CharLinkedList:: specified_node (Node *curr, int count,
                                                         int index) const {
    if (count == index) {
        return curr;
    }
    return specified_node(curr->next, count + 1, index);
}

//Function that inserts the given character at the specified index.
/*
 * name: insertAt    
 * purpose: Function that inserts the given character at the specified index.
 * arguments: a character to insert and the index at which to insert in the
 * list
 * returns: Nothing
 * effects: Allocates new memory for one new node
 */ 
void CharLinkedList::insertAt(char c, int index) {

    if (index < 0 or index > num_nodes ) {
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + "]"); 
    } else if (index == 0) { //if index 0, that means u want to insert at front
        this->pushAtFront(c);///num_nodes incremented here
    } else if (index > 0 and index < num_nodes) { //if greater than 0 and less 
        //than size, then u want to insert between 2 nodes
        Node *curr = front;
        Node *node_before = specified_node(curr, 0, index - 1);
        Node *new_node = new Node;
        new_node->prev = node_before;
        new_node->next = node_before->next;
        node_before->next = new_node;
        new_node->next->prev = new_node;
        new_node->data = c;
        num_nodes++;
    } else if (index == num_nodes) { //if want to insert at index ==size,
        //then push at back
        this->pushAtBack(c);
    }
}

/*
 * name: insertInOrder   
 * purpose: Inserts the given element into the list in ASCII order
 * arguments: a character to insert into the list 
 * returns: Nothing
 * effects: It allocates memory for a new node.
 */
void CharLinkedList::insertInOrder(char c) {

    if(this->isEmpty()) {
        pushAtFront(c);
    } //no need for else b/c if is empty, then num_nodes is 0 and it would not 
    //even enter the loop
    //if num_nodes is greater than 0
    for (int i = 0; i < this->num_nodes; i++) {
        char current_char = this->elementAt(i);
        if (current_char > c) {
            insertAt(c, i);
            i = this->size() + 1; //to break out of loop
        }
    }
}

/*
 * name: popFromBack     
 * purpose: Function that removes the last element from the list  
 * arguments: None
 * returns: Nothing
 * effects: It recycles the memory for one node by removing the last
 * element from the list
 */
void CharLinkedList::popFromBack() {
    if (this->isEmpty()) {
        throw runtime_error("cannot pop from empty LinkedList"); 
    } else {
        Node *last_node = specified_node(front, 0, num_nodes - 1);
        last_node->prev->next = nullptr;
        delete last_node;
        num_nodes--;
    }
}

/*
 * name: popFromFront     
 * purpose: Function that removes the first element from the list  
 * arguments: None
 * returns: Nothing
 * effects: It recycles the memory for one node by removing the first
 * element from the list 
 */
void CharLinkedList::popFromFront() {
    if (this->isEmpty()) {
        throw runtime_error("cannot pop from empty LinkedList"); 
    } else {
        //front is the first node
        front->next->prev = nullptr;
        Node *old_front=  front;
        front = front->next;
        delete old_front;
        num_nodes--;
    }
}

/*
 * name: removeAt     
 * purpose: Function that removes the element at the specified index  
 * arguments: An index indicatin which element to remove
 * returns: Nothing
 * effects: It recycles the memory for one node by removing the element
 * at the specified index
 */
void CharLinkedList::removeAt(int index) { 
    if (index < 0 or index >= num_nodes ) {
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + ")"); 
    } else if (index == 0) { 
        //removing index 0 is the same as popping from front
        this->popFromFront();
    } else if (index > 0 and index < this->size() - 1 ) {
        //Removing a node between 2 nodes
        Node *desired_node = specified_node(front, 0, index);
        //(desired node is between first and second)
        //first node points to second
        desired_node->prev->next = desired_node->next;
        //second node points to first node
        desired_node->next->prev = desired_node->prev;
        delete desired_node;
        num_nodes--;
    } else if (index == this->size() - 1) { //if removing last node
        //
        this->popFromBack();
    }
}

/*
 * name: replaceAt      
 * purpose: Function that replaces the element at the specified index 
 * with the new element 
 * arguments: A character to replace another element at the specified index
 * returns: Nothing
 * effects: Changes around pointers and dealloctes and allocates memory to 
 * replace a node 
 */
void CharLinkedList::replaceAt(char c, int index) {
    //first remove at if out of range
    if (index < 0 or index >= num_nodes ) {
        throw range_error("index (" + to_string(index) + ") not in range [0.."
        + to_string(this->size()) + ")"); 
    //if want to replace first node
    } else if (index == 0) { //removing index 0 is the same as 
    //popping from front
        this->popFromFront();
        this->insertAt(c, index);
    } else if (index > 0 and index < this->size() - 1 ) { 
        //if we want to remove a node b/t 2 nodes
        Node *desired_node = specified_node(front, 0, index); 
        //(desired node is between first and second)
        //first node points to second
        desired_node->prev->next = desired_node->next;
        //second node points to first node
        desired_node->next->prev = desired_node->prev;
        delete desired_node;
        num_nodes--;
        this->insertAt(c, index);
    } else if (index == this->size() - 1) { //if removing/inserting last node
        //
        this->popFromBack();
        this->insertAt(c, index);
    }
}

//Function that adds a copy of the list pointed to by other to the end of the
//list that called the function
/*
 * name: concatenate     
 * purpose: Function that adds a copy of the list pointed to by other to 
 * the end of the list that called the function 
 * arguments: An pointer to a CharLinkedList object 
 * returns: Nothing 
 * effects: Adds a copy of the other list to the end of the list.
 */
void CharLinkedList::concatenate(CharLinkedList *other) {
    //adding elements of other to the back of this list
    int initial_size_other = other->size();
    for (int i = 0; i < initial_size_other; i++) {
        this->pushAtBack(other->elementAt(i));
    }
}


