/*
 *  unit_tests.h
 *  Javier Laveaga
 *  09/21/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  To test the different functions/methods in the Character Linked List class
 *  
 *
 */
#include "CharLinkedList.h"
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

void test_empty () {
    CharLinkedList list;
    assert(list.isEmpty());
}
void test_empty_filled () {
    CharLinkedList list('x');
    assert(not(list.isEmpty()));
}
void test_constructor() {
    CharLinkedList list;
    assert(list.size() == 0);
}
void test_size () {
    CharLinkedList list('x');
    assert(list.size() == 1);
}
void test_size_empty () {
    CharLinkedList list;
    assert(list.size() == 0);
}

void test_constructor_2 () {
   // cout << "Before Creation" << endl;
    CharLinkedList list('a');
    //cout << "After Creation" << endl;
    //assert(list.size() == 1);
    //cout << "After Assert" << endl;

    //assert that element at 0 has the letter a.
    assert(list.first() == 'a');
}

void test_constructor_3 () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list(arr, 3);
    string message = list.toString();
    assert(message == "[CharLinkedList of size 3 <<abc>>]");
    //cout << list.front->data << endl;
    //Test with with to String function
}


void test_copy_constructor () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list1(arr, 3);
    CharLinkedList list2(list1);
    assert(list2.toString() == "[CharLinkedList of size 3 <<abc>>]");
    //see if changing one list will affect the other
    list1.popFromBack();
    assert(list1.size() == 2);
    assert(list2.size() == 3);
}

void test_copy_constructor_empty() {
    CharLinkedList list1;
    CharLinkedList list2(list1);
    assert(list2.toString() == "[CharLinkedList of size 0 <<>>]");
}



void test_push_at_front () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list(arr, 3);
    list.pushAtFront('x');
    string message = list.toString();
    assert(message == "[CharLinkedList of size 4 <<xabc>>]");
}

void test_push_at_front_empty () {
    CharLinkedList list;
    list.pushAtFront('x');
    string message = list.toString();
    assert(message == "[CharLinkedList of size 1 <<x>>]");
    list.pushAtFront('y');
    message = list.toString();
    assert(message == "[CharLinkedList of size 2 <<yx>>]");
}


void test_push_at_back () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list(arr, 3);
    list.pushAtBack('d');
    string message = list.toString();
    assert(message == "[CharLinkedList of size 4 <<abcd>>]");
}

void test_push_at_back_empty () {
    CharLinkedList list;
    list.pushAtBack('x');
    string message = list.toString();
    assert(message == "[CharLinkedList of size 1 <<x>>]");
}

void test_to_string () {
    char arr[] = { 'h', 'e', 'l' , 'l', 'o'};
    CharLinkedList list(arr, 5);
    assert(list.toString() == "[CharLinkedList of size 5 <<hello>>]");
}

void test_to_String_empty () {
    CharLinkedList list;
    assert(list.toString() == "[CharLinkedList of size 0 <<>>]");
}

void test_to_Reverse_string() {
    char arr[] = { 'a', 'b', 'c'};
    CharLinkedList list(arr, 3);
    //list.front->prev = nullptr;
    assert(list.toReverseString() == "[CharLinkedList of size 3 <<cba>>]");
}

void test_Reverse_string_empty () {
    CharLinkedList list;
    assert(list.toReverseString() == "[CharLinkedList of size 0 <<>>]");
}

void test_first () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list(arr, 3);
    assert(list.first() == 'a');
}

void test_first_empty () {
    //copy
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList list;
    try {
     //Testing runtime error with empty list
    list.first();
    }
    catch (const std::runtime_error &e) {
    // if first is correctly implemented, a runtime_error will be thrown,
    // and we will end up here
    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
    //copy
}

void test_last () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list(arr, 3);
    assert(list.last() == 'c');
}

void test_last_empty () {
    //copy
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList list;
    try {
        //Testing runtime error with empty list
        list.last();
    }
    catch (const std::runtime_error &e) {
    // if first is correctly implemented, a runtime_error will be thrown,
    // and we will end up here
    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty LinkedList");
    //copy
}

void test_clear () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list(arr, 3);
    list.clear();
    assert(list.isEmpty());
}

void test_clear_empty () {
    CharLinkedList list;
    list.clear();
    assert(list.isEmpty());
}

void test_assignment_operator() {
    //test to see if first condition works (empty list)
    CharLinkedList list1;
    list1 = list1; 
    assert(list1.isEmpty());
}

void test_assignment_operator_2() {
    //fist condition. (filled list)
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list2(arr, 3);
    list2 = list2;
    assert(list2.first() == 'a');
}

void test_assignment_operator_3() {
    //test when other is empty list (tests else case)
    CharLinkedList list1;
    CharLinkedList list3;
    list1 = list3;
    assert(list1.isEmpty());
}

void test_assignment_operator_4() {
    //test when other is filled (tests while loop)
    //making empty list a filled list
    CharLinkedList list1;
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list2(arr, 3);
    list1 = list2;
    assert(list1.first() == 'a');
}

void test_assignment_operator_5() {
    //making a filled list an empty list
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list2(arr, 3);
    CharLinkedList list3;

    list2 = list3; 
    assert(list2.isEmpty());
}

void test_element_at () {
    char arr[] = { 'a', 'b', 'c' };
    CharLinkedList list1(arr, 3);
    //assert(list1.elementAt(1) == 'b');
    assert(list1.elementAt(0) == 'a');
    assert(list1.elementAt(1) == 'b');
    assert(list1.elementAt(2) == 'c');
}

void test_elementAt_invalid () {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    char sample[] = {'h','e','l','l','o'};
    CharLinkedList list1(sample, 5);

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

void test_elementAt_empty () {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList list1;

    try {
        // insertAt for out-of-range index
        list1.elementAt(0);
    
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

void test_InsertAt () {
    //Inserting at beginning 
    char arr[] = { 'a', 'b', 'c', 'd'};
    CharLinkedList list1(arr, 4);
    list1.insertAt('x', 0);
    assert(list1.toString() == "[CharLinkedList of size 5 <<xabcd>>]");
}

void test_InsertAt_middle () {
    //Inserting somewhere in the middle
    char arr[] = { 'a', 'b', 'c', 'd'};
    CharLinkedList list2(arr, 4);
    list2.insertAt('y', 2);
    assert(list2.toString() == "[CharLinkedList of size 5 <<abycd>>]");
}

void test_InsertAt_back () {
    //Inserting at index = size
    char arr[] = { 'a', 'b', 'c', 'd'};
    CharLinkedList list3(arr, 4);
    list3.insertAt('z', 4);
    assert(list3.toString() == "[CharLinkedList of size 5 <<abcdz>>]");
}
//Test insert at out of range
void test_InsertAt_invalid () {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    char arr[] = { 'a', 'b', 'c', 'd'};
    CharLinkedList list1(arr, 4);

    try {
        // insertAt for out-of-range index
        list1.insertAt('x', 5);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (5) not in range [0..4]");
}

//Test insert at with empty list
void test_insertAt_empty () {
    CharLinkedList list1;
    list1.insertAt('x', 0);
    assert(list1.elementAt(0) == 'x');
}

void test_insertAt_empty_invalid () {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList list1;

    try {
        // insertAt for out-of-range index
        list1.insertAt('x', 1);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (1) not in range [0..0]");
}

void test_insertInOrder () {
    char arr[] = { 'a', 'b', 'd', 'e', 'f' };
    CharLinkedList list1(arr, 5);
    list1.insertInOrder('c');
    assert(list1.elementAt(2) == 'c');
}

void test_insertInOrder_2 () {
    //Testing differently ordered list
    char arr2[5] = { 'Z', 'E', 'D'};
    CharLinkedList list2(arr2, 3);
    list2.insertInOrder('A');
    assert(list2.elementAt(0) == 'A');
    assert(list2.toString() == "[CharLinkedList of size 4 <<AZED>>]" );
}

void test_insertInOrder_empty() {
    CharLinkedList list;
    list.insertInOrder('x');
    assert(list.toString() == "[CharLinkedList of size 1 <<x>>]" );
}

void test_insertInOrder_3 () {
    //Testing differently ordered list
    char arr2[4] = { 'a', 'b', 'c', 'd'};
    CharLinkedList list2(arr2, 4);
    list2.insertInOrder('7');
    assert(list2.toString() == "[CharLinkedList of size 5 <<7abcd>>]" );
}



void test_popFromBack () {
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list1(arr, 5);
    list1.popFromBack();
    assert(list1.toString() == "[CharLinkedList of size 4 <<abcd>>]" );

}

void test_popFromBack_empty () {
    bool runtime_error_thrown = false;
    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList list1;
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
    assert(error_message == "cannot pop from empty LinkedList");
}

void test_popFromFront () {
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list1(arr, 5);
    list1.popFromFront();
    assert(list1.toString() == "[CharLinkedList of size 4 <<bcde>>]");
}

void test_popFromFront_empty () {
    bool runtime_error_thrown = false;
    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList list1;
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
    assert(error_message == "cannot pop from empty LinkedList");
}

void test_RemoveAt_middle () {
    //Removing something in the middle -passed
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list1(arr, 5);
    list1.removeAt(1);
    assert(list1.toString() == "[CharLinkedList of size 4 <<acde>>]");
}

void test_RemoveAt_first () {
    //Removing first node
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list2(arr, 5);
    list2.removeAt(0);
    assert(list2.toString() == "[CharLinkedList of size 4 <<bcde>>]");
}

void test_RemoveAt_last () {
    //Removing last node
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list3(arr, 5);
    list3.removeAt(4);
    assert(list3.toString() == "[CharLinkedList of size 4 <<abcd>>]");
}

void test_RemoveAt_invalid () {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    char sample[] = {'h','e','l','l','o'};
    CharLinkedList list1(sample, 5);

    try {
        // removeAt for out-of-range index
        list1.removeAt(-1);
    
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (-1) not in range [0..5)");
}

void test_replaceAt_middle () {
    //Removing something in the middle -passed
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list1(arr, 5);
    list1.replaceAt('x', 2);
    assert(list1.toString() == "[CharLinkedList of size 5 <<abxde>>]");
}

void test_replaceAt_first () {
    //Replacing at first node
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list2(arr, 5);
    list2.replaceAt('x', 0);
    assert(list2.toString() == "[CharLinkedList of size 5 <<xbcde>>]");
}

void test_replaceAt_last () {
    //Replacing last node
    char arr[] = { 'a', 'b', 'c', 'd', 'e' };
    CharLinkedList list3(arr, 5);
    list3.replaceAt('x', 4); 
    assert(list3.toString() == "[CharLinkedList of size 5 <<abcdx>>]");
}

void test_replaceAt_invalid () {
    bool range_error_thrown = false;
    // var to track any error messages raised
    std::string error_message = "";

    char sample[] = {'h','e','l','l','o'};
    CharLinkedList list1(sample, 5);

    try {
        // removeAt for out-of-range index
        list1.replaceAt('c', 5);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (5) not in range [0..5)");
}

//Testing concatenate function (list with another list)
void test_concatenate () {
    char test_arr[5] = { 'h', 'e', 'l'};
    CharLinkedList test_list(test_arr, 3);
    
    char test_arr2[7] = { 'a', 'r'};
    CharLinkedList test_list2(test_arr2, 2);

    test_list2.concatenate(&test_list);
    assert(test_list2.toString() == "[CharLinkedList of size 5 <<arhel>>]");
}

//Testing concatenate function (empty + filled array list)
void test_concatenate_empty () {
    CharLinkedList list1;
    char test_arr[3] = { 'h', 'e', 'l'};
    CharLinkedList test_list(test_arr, 3);
    list1.concatenate(&test_list);
    //should be the same as last time
    assert(list1.toString() == "[CharLinkedList of size 3 <<hel>>]");
}

//Testing concatenate function (filled array list + empty)
void test_concatenate_empty_2 () {
    CharLinkedList list1;
    char test_arr[3] = { 'h', 'e', 'l'};
    CharLinkedList test_list(test_arr, 3);
    test_list.concatenate(&list1);

    assert(test_list.toString() == "[CharLinkedList of size 3 <<hel>>]");
}

//Test concatenate function (with itself)
void test_concatenate_itself () {
    char test_arr[3] = { 'h', 'e', 'l'};
    CharLinkedList test_list(test_arr, 3);

    test_list.concatenate(&test_list);
    assert(test_list.toString() == "[CharLinkedList of size 6 <<helhel>>]");
}

//empty with empty
void test_concatenat_empty_3 () {
    CharLinkedList list1;
    CharLinkedList list2;
    list1.concatenate(&list2);
    assert(list1.toString() == "[CharLinkedList of size 0 <<>>]");
}


