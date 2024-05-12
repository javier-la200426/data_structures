/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 * edited by: Javier Laveaga September 2023
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */
#include "CharArrayList.h"
#include <cassert>


/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */

//Testing Default Constructor
void test_constructor () {
    CharArrayList list; //use get size to cout size and tst
    assert(list.size() == 0);
  
}

//Testing Second Constructor
void test_second_constructor () {
    CharArrayList list('s');
    assert(list.elementAt(0) == 's');
    //cout << list.data[0]<< endl; //use get element function to test & print out element
}

//Testing third constructor
void test_third_constructor () {
    char sample[] = {'s','u','p'};
    CharArrayList list(sample, 3);
    assert(list.elementAt(0) == 's');
    assert(list.elementAt(1) == 'u');
    assert(list.elementAt(2) == 'p');
}

//Testing Copy Constructor
void test_copy_constructor () {
    //initializng list2 from a default list
    CharArrayList list1;
    CharArrayList list2(list1);

    //HERE: test to change 
    list1.pushAtBack('y');
    assert(list1.size() == 1);
    assert(list2.size() == 0);

    //Initializing list 4 from a list created with 2nd constructor
    CharArrayList list3('s');
    CharArrayList list4(list3);
    //print out elements of list4
    assert(list4.elementAt(0) == 's');

    //Initializing list 6 with the third constructor
    char sample[] = {'s','u','p'};
    CharArrayList list5(sample, 3);
    CharArrayList list6(list5);
    assert(list6.elementAt(0) == 's');
    assert(list6.elementAt(1) == 'u');
    assert(list6.elementAt(2) == 'p');
}

//Testing assignment operator
void test_assignment_operator() {
    //test to see if first condition works 
    CharArrayList list1;
    list1 = list1; 
    assert(list1.capacity() == 0);

    //test to see if it works when data is nullptr
    CharArrayList list2;
    list1 = list2;
    assert(list1.capacity() == 0);

    //test to see when other.data is pointing to st
    char sample[] = {'s','u','p'};
    CharArrayList list3(sample, 3);
    list1 = list3;
    assert(list1.capacity() == 3);
}

//Testing the isEmpty function
void test_isEmpty() {
    //test when a list is empty
    CharArrayList list1;
    bool isEmpty = list1.isEmpty();
    assert(isEmpty == 1);

    //test when list is not empty
    CharArrayList list2('s');
    isEmpty = list2.isEmpty();
    assert(isEmpty == 0);
}

// Testing the clear function
void test_clear() {
    //crete a filled array list
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    assert(list1.elementAt(3) == 'l'); // to see an element in list
    
    bool isEmpty = list1.isEmpty(); 
    assert(isEmpty == 0);

    list1.clear();
    isEmpty = list1.isEmpty();
    assert(isEmpty == 1);
    //Output: l,1,0
}

// Testing first character function
void test_first_char() {
    //Returning first character of filled list
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    char first_char = list1.first();
    assert(first_char == 'h');
    
    //cout << first_char << endl; //should be h
}

//Testing returning first character on empty list
void test_first_char_incorrect() {
    //Testing runtime error with empty list

    //copy
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList list2;
    try {
     //Testing runtime error with empty list
    list2.first();
    }
    catch (const std::runtime_error &e) {
    // if first is correctly implemented, a range_error will be thrown,
    // and we will end up here
    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty ArrayList");

    //copy
}

// Testing the last character function
void test_last_char() {
    //Returning last character of filled list
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    char last_char = list1.last();
    assert(last_char == 'o');
    //cout << last_char << endl; //should be o
}

//Testing the las character function on empty list
void test_last_char_incorrect () {

    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList list2;
    try {
        //Testing runtime error with empty list
        list2.last();
    }
    catch (const std::runtime_error &e) {
    // if first is correctly implemented, a runtime_error will be thrown,
    // and we will end up here
    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty ArrayList");
}

//Testing elementAt function with index in range
void test_element_at () {
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    char element = list1.elementAt(1);
    assert(element ==  'e');
}

//Testing elementAt when the element is not in range
void test_element_at_incorrect () {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    try {
    // insertAt for out-of-range index
    list1.elementAt(6);
    
    }
    catch (const std::range_error &e) {
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..5)");
}

//Testing function that returns a string containing the characters of the 
// Character Array list
void test_toString () {
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    assert(list1.toString() == "[CharArrayList of size 5 <<hello>>]");
    
    //When array list is empty
    CharArrayList list2;
    assert(list2.toString() == "[CharArrayList of size 0 <<>>]");
}

//Testing function that returns a string containing the characters of the
// character array list in reverse order
void test_toReverseString() {
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    assert(list1.toReverseString() == "[CharArrayList of size 5 <<olleh>>]");

    //When array list is empty
    CharArrayList list2;
    assert(list2.toReverseString() == "[CharArrayList of size 0 <<>>]");
}

//Test function that expands the capacity
void test_expand () {

    //Test list of size and capacity = 0;
    CharArrayList list;
    //call push at back to expand
    //list.expand();
    list.pushAtBack('s');
    assert(list.size() == 1); //size should increase by 1
    assert(list.capacity() == 2);

    //Test list of size and capacity greater than 0
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list2(sample, 5);
    //call push at back to expand
    //list2.expand();
    list2.pushAtBack('x');
    assert(list2.size() == 6); //size should increase by 1
    assert(list2.capacity() == 12);
}

//Test function that inserts the given new element in front of the existing elements
// in the array list
void test_push_at_back (){
    //Test when Capacity = Size
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    list1.pushAtBack('s');
    assert(list1.elementAt(5) == 's');
    
    //Tests when Capacity > Size
    list1.pushAtBack('x');
    assert(list1.elementAt(6) == 'x');
}

//Tests push at back for an empty list
void test_push_back_empty_list() {
    CharArrayList list;
    list.pushAtBack('y');
    assert(list.elementAt(0) == 'y');
}


//tests push at front when not empty
void test_push_at_front () {
    //Tests when Capacity = Size
    char sample[] = {'h','e','l','l','o'};
    CharArrayList list1(sample, 5);
    list1.pushAtFront('c');
    assert(list1.elementAt(0) == 'c');
    
    //Tests when Capacity > Size
    list1.pushAtFront('u');
    assert(list1.elementAt(0) == 'u');
}

//Tests push at front for an empty list
void test_push_front_empty_list() {
    CharArrayList list;
    list.pushAtFront('s');
    assert(list.elementAt(0) == 's');
}

// /* Jav

// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 

    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');

}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
    
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}

// Tests insertion into front of a larger list
void insertAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 9);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 10);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString() ==     "[CharArrayList of size 10 <<yabczdefgh>>]");

}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 10);  

    test_list.insertAt('x', 10);

    assert(test_list.size() == 11);
    assert(test_list.elementAt(10) == 'x');
    assert(test_list.toString() == 
    "[CharArrayList of size 11 <<yabczdefghx>>]"); 

}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() ==     "[CharArrayList of size 9 <<abczdefgh>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}
// Jav */

//Testing insert in Order function
void test_insert_in_order () {
    char test_arr[5] = { 'a', 'b', 'd', 'e', 'f'};
    CharArrayList test_list(test_arr, 5);
    test_list.insertInOrder('c');
    assert(test_list.elementAt(2) == 'c');

    //Testing differently ordered list
    char test_arr2[5] = { 'Z', 'E', 'D'};
    CharArrayList test_list2(test_arr2, 3);
    test_list2.insertInOrder('A');
    assert(test_list2.elementAt(0) == 'A');
}

//Testing pop Front function
void test_pop_front () {

    //Testing non-empty list
    char test_arr[5] = { 'h', 'e', 'l', 'l', 'o'};
    CharArrayList test_list(test_arr, 5);
    test_list.popFromFront();
    assert(test_list.elementAt(0) == 'e');
    //Size is one less. From 5 to 4. 
    assert(test_list.size() == 4);
}

//Testing pop front function with empty list
void test_pop_front_empty_incorrect() {
    
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList list1;
    try {
        //Testing runtime error with empty list
        list1.popFromFront();
    }
    catch (const std::runtime_error &e) {
    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}


//Testing pop back function 
void test_pop_back() {
    char test_arr[5] = { 'h', 'e', 'x', 'l', 'o'};
    CharArrayList test_list(test_arr, 5);
    test_list.popFromBack();
    //last element should be 'l'
    assert(test_list.elementAt(test_list.size() - 1) == 'l');
}

//Testing pop back function with empty list
void test_pop_back_empty_incorrect() {
    
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList list1;
    try {
        //Testing runtime error with empty list
        list1.popFromBack();
    }
    catch (const std::runtime_error &e) {
    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

//Testing remove_at function
void test_remove_at () {
    //Testing valid index
    char test_arr[5] = { 'h', 'e', 'x', 'l', 'o'};
    CharArrayList test_list(test_arr, 5);
    test_list.removeAt(1);
    assert(test_list.elementAt(1) == 'x');
}

//Testing remove at with invalid index
void test_remove_at_incorrect () {

     // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    char test_arr[5] = { 'h', 'e', 'l', 'l', 'o'};
    CharArrayList test_list(test_arr, 5);
    try {
        test_list.removeAt(5);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (5) not in range [0..5)");
}


//Testing removeAt with empty list
void test_remove_at_empty_incorrect () {
   
     // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        test_list.removeAt(0);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

//Testing replace at
void test_replace_at () {
    char test_arr[5] = { 'h', 'e', 'l', 'l', 'o'};
    CharArrayList test_list(test_arr, 5);
    test_list.replaceAt('x', 1);
    assert(test_list.elementAt(1) == 'x');
}

//Testing replace at out of range index
void test_replace_at_incorrect () {
   
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    char test_arr[5] = { 'h', 'e', 'l', 'l', 'o'};
    CharArrayList test_list(test_arr, 5);

    try {
    // insertAt for out-of-range index
    test_list.replaceAt('x', 6);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..5)");
}

//Testing replace at in empty list
void test_repl_at_empt_incorrec () {
  
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;

    try {
    // insertAt for out-of-range index
    test_list.replaceAt('x', 6);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..0)");  
}

//Testing concatenate function (list with another list)
void test_concatenate () {
    char test_arr[5] = { 'h', 'e', 'l'};
    CharArrayList test_list(test_arr, 3);
    
    char test_arr2[7] = { 'a', 'r'};
    CharArrayList test_list2(test_arr2, 2);

    test_list2.concatenate(&test_list);
    assert(test_list2.elementAt(2) == test_list.elementAt(0));
    assert(test_list2.elementAt(3) == test_list.elementAt(1));
    assert(test_list2.elementAt(4) == test_list.elementAt(2));
}

//Testing concatenate function (empty + filled array list)
void test_concatenate_empty () {
    CharArrayList list1;
    char test_arr[5] = { 'h', 'e', 'l'};
    CharArrayList test_list(test_arr, 5);
    list1.concatenate(&test_list);
    //should be the same as last time
    assert(list1.elementAt(0) == 'h');
    assert(list1.elementAt(1) == 'e');
    assert(list1.elementAt(2) == 'l');
}

//Testing concatenate function (filled array list + empty)
void test_concatenat_empty_2 () {
    CharArrayList list1;
    char test_arr[5] = { 'h', 'e', 'l'};
    CharArrayList test_list(test_arr, 5);
    test_list.concatenate(&list1);

    assert(test_list.elementAt(0) == 'h');
    assert(test_list.elementAt(1) == 'e');
    assert(test_list.elementAt(2) == 'l');
}

//Test concatenate function (with itself)
void test_concatenate_itself () {
    char test_arr[5] = { 'h', 'e', 'l'};
    CharArrayList test_list(test_arr, 3);

    test_list.concatenate(&test_list);

    assert(test_list.elementAt(0) == 'h');
    assert(test_list.elementAt(1) == 'e');
    assert(test_list.elementAt(2) == 'l');
    assert(test_list.elementAt(3) == 'h');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'l');
}

