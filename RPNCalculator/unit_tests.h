/*
 * unit_tests.h
 *
 * COMP 15 Project 2: CalcYouLater
 * 
 * Tests the DatumStack class, the Parser function, and 
 * the methods in the RPNCalc class. For many of those 
 * functions, it uses the print function of
 * DatumStack and stringstreams to check that the correct 
 * Datums are in the stack.
 * 
 * Creates 4 Datum object for reuse in multiple tests.
 * 
 * Edited by Javier Laveaga (jlavea01) Monday, October 16.
 */

#include "RPNCalc.h"
#include <cassert>
#include <string>
#include <sstream> 
#include "parser.h"
#include <fstream>
using namespace std;


/*
 * name: check_open
 * purpose: Checks to see if the input or output file can be opened. This
 * is used only to test parseString.
 * arguments: Either the commands file or the output file to be used
 * returns: Nothing 
 * effects: Will throw an error if there is an error opening the file
 */
template<typename streamtype>
void check_open(streamtype &stream, string file_name) {
        stream.open(file_name);
        if (not stream.is_open()) {
                cerr << "Error: could not open file " << file_name << endl;
                exit(EXIT_FAILURE);
        }
 }


Datum num(2);
Datum boolean(true);
Datum text("hello");

//DatumStack tests
void test_constructor_Datum() {
    DatumStack stack_t;
    assert(stack_t.size() == 0);
}

//testing second constructor
void test_constructor_two () {
    stringstream sstream;
    Datum arr[3] = {num, boolean, text};
    DatumStack stack_t(arr, 3);
    stack_t.print(sstream);
    assert(sstream.str() == "2#thello");
}

void test_clear_empty() {
    DatumStack stack_t;
    stack_t.clear();
}

void test_clear_filled() {
    DatumStack stack_t;
    stack_t.push(num);
    stack_t.push(boolean);
    stack_t.push(text);
    assert(stack_t.size() == 3);
    stack_t.clear();
    assert(stack_t.size() == 0);
}

void test_size() {
    DatumStack stack_t;
    assert(stack_t.size() == 0);
}

//Adding one element
void test_push_1() {
    DatumStack stack_t;
    stringstream sstream;
    stack_t.push(num);
    assert(stack_t.size() == 1);
    stack_t.print(sstream);
    assert(sstream.str() == "2");
}

//Adding multiple elements
void test_push_2() {
    DatumStack stack_t;
    stringstream sstream;
    stack_t.push(num);
    stack_t.push(boolean);
    stack_t.push(text);
    assert(stack_t.size() == 3);
    stack_t.print(sstream);
    assert(sstream.str() == "2#thello");
}

void test_top () {
    DatumStack stack_t;
    stack_t.push(num);
    stack_t.push(boolean);
    stack_t.push(text);
    Datum example(stack_t.top());
    assert(example.toString() == "hello"); 
}

void test_top_empty () {
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    DatumStack stack_t;
    try {
        stack_t.top();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void test_pop () {
    stringstream sstream;
    Datum arr[3] = {num, boolean, text};
    DatumStack stack_t(arr, 3);
    assert(stack_t.size() == 3);
    stack_t.pop();
    stack_t.print(sstream);
    assert(sstream.str() == "2#t");
    assert(stack_t.size() == 2);
}

void test_pop_empty () {
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    DatumStack stack_t;
    try {
        stack_t.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}
//
//Parse String tested w/different input files
//
void test_parse_1 () {
    ifstream infile;

    check_open(infile, "Parse_t1.cylc");
    string sample_s = parseRString(infile);
    assert(sample_s == "{ 1 2 + }");
    infile.close();
}

void test_parse_2 () {
    ifstream infile;

    check_open(infile, "Parse_t2.cylc");
    string sample_s = parseRString(infile);
    assert(sample_s == "{ 1 { 4 2 / } / }");
    infile.close();
}

void test_parse_3 () {
    ifstream infile;

    check_open(infile, "Parse_t3.cylc");
    string sample_s = parseRString(infile);
    assert(sample_s == "{ 1 2 + }");
    infile.close();
}
//
//TESTS FOR RPNCalc BEGIN (made stack temporarily public)
//

void test_constructor_RPN () {
    RPNCalc test;
}

void test_push_datum () {
    RPNCalc test;
    test.push_datum(num);
    test.push_datum(num);
    assert(test.stack.size() == 2);
}

void test_not_datum() {
    stringstream ss;
    RPNCalc test;
    test.push_datum(num);
    test.push_datum(boolean);
    //Before not_datum
    test.stack.print(ss);
    assert(ss.str() == "2#t");
    ss.str(""); //clear stream
    //after not_datum
    test.not_datum("not");
    test.stack.print(ss);
    assert(ss.str() == "2#f");
}

void test_not_datum_not_bool() {
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    RPNCalc test;
    test.push_datum(num);
    try {
        test.not_datum("not");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "datum_not_bool");
}

void test_not_datum_empty () {
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    RPNCalc test;
    try {
        test.not_datum("not");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void test_print () {
    RPNCalc test;
    test.push_datum(num);
    test.push_datum(boolean);
    test.push_datum(text);
    test.print("print");
}

void test_print_empty () {
    bool runtime_error_thrown = false;
   
    std::string error_message = "";

    RPNCalc test;
    try {
        test.print("print");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void test_clear () {
    RPNCalc test;
    test.push_datum(num);
    test.push_datum(boolean);
    test.push_datum(text);
    assert(test.stack.size() == 3);
    test.clear("clear");
    assert(test.stack.size() == 0);
}

void test_clear_empty_RPN () {
    RPNCalc test;
    assert(test.stack.size() == 0);
    test.clear("clear");
    assert(test.stack.size() == 0);
}

void test_drop () {
    stringstream ss;
    RPNCalc test;
    test.push_datum(num);
    test.push_datum(boolean);
    test.push_datum(text);
    test.stack.print(ss);
    assert(ss.str() == "2#thello");
    ss.str(""); //clear stream
    //after not_datum
    test.drop("drop");
    test.stack.print(ss);
    assert(ss.str() == "2#t");
}

void test_drop_empty () {
    bool runtime_error_thrown = false;
   
    std::string error_message = "";

    RPNCalc test;
    try {
        test.drop("drop");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void test_dup () {
    stringstream ss;
    RPNCalc test;
    test.push_datum(num);
    test.push_datum(boolean);
    test.push_datum(text);
    test.stack.print(ss);
    assert(ss.str() == "2#thello");
    ss.str(""); //clear stream
    //after not_datum
    test.dup("dup");
    test.stack.print(ss);
    assert(ss.str() == "2#thellohello");
}

void test_dup_empty () {
    bool runtime_error_thrown = false;
   
    std::string error_message = "";

    RPNCalc test;
    try {
        test.dup("dup");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void test_swap () {
    stringstream ss;
    RPNCalc test;
    test.push_datum(num);
    test.push_datum(boolean);
    test.push_datum(text);
    test.stack.print(ss);
    assert(ss.str() == "2#thello");
    ss.str(""); //clear stream
    //after not_datum
    test.swap("swap");
    test.stack.print(ss);
    assert(ss.str() == "2hello#t");
}

void test_swap_empty() {
    bool runtime_error_thrown = false;
   
    std::string error_message = "";

    RPNCalc test;
    try {
        test.swap("swap");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void test_operation_add () {
    RPNCalc test;
    stringstream ss;
    Datum num_3(3);
    test.push_datum(num);
    test.push_datum(num_3);
    test.stack.print(ss);
    assert(ss.str() == "23");
    ss.str(""); //clear stream
    test.operation("+");
    test.stack.print(ss);
    assert(ss.str() == "5");
}

void test_operation_sub () {
    RPNCalc test;
    stringstream ss;
    Datum num_3(3);
    test.push_datum(num);
    test.push_datum(num_3);
    test.stack.print(ss);
    assert(ss.str() == "23");
    ss.str(""); //clear stream
    test.operation("-");
    test.stack.print(ss);
    assert(ss.str() == "-1");
}

void test_operation_multi () {
    RPNCalc test;
    stringstream ss;
    Datum num_3(3);
    test.push_datum(num);
    test.push_datum(num_3);
    test.stack.print(ss);
    assert(ss.str() == "23");
    ss.str(""); //clear stream
    test.operation("*");
    test.stack.print(ss);
    assert(ss.str() == "6");
}

void test_operation_divi () {
    //15/3 should be 5
    RPNCalc test;
    stringstream ss;
    Datum num_3(3);
    Datum num_15(15);
    test.push_datum(num_15);
    test.push_datum(num_3);
    test.stack.print(ss);
    assert(ss.str() == "153");
    ss.str(""); //clear stream
    test.operation("/");
    test.stack.print(ss);
    assert(ss.str() == "5");
}

void test_operation_mod () {
    RPNCalc test;
    stringstream ss;
    Datum num_3(3);
    Datum num_15(5);
    test.push_datum(num_15);
    test.push_datum(num_3);
    test.stack.print(ss);
    assert(ss.str() == "53");
    ss.str(""); //clear stream
    test.operation("mod");
    test.stack.print(ss);
    assert(ss.str() == "2");
}

void test_operation_notInt () {
    RPNCalc test;
    stringstream ss;
    test.push_datum(num);
    test.push_datum(boolean);
    test.stack.print(ss);
   
    bool runtime_error_thrown = false;
   
    std::string error_message = "";

    try {
        test.operation("+");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "datum_not_int");
}

void test_bool_operation_less() {
    RPNCalc test;
    stringstream ss;
    Datum num_3(3);
    Datum num_5(5);
    test.push_datum(num_5);
    test.push_datum(num_3);
    test.stack.print(ss);
    assert(ss.str() == "53");
    ss.str(""); //clear stream
    test.bool_operation("<");
    test.stack.print(ss);
    assert(ss.str() == "#f");
}

void test_bool_operation_great() {
    RPNCalc test;
    stringstream ss;
    Datum num_3(3);
    Datum num_5(5);
    test.push_datum(num_5);
    test.push_datum(num_3);
    test.stack.print(ss);
    assert(ss.str() == "53");
    ss.str(""); //clear stream
    test.bool_operation(">");
    test.stack.print(ss);
    assert(ss.str() == "#t");
}

void test_bool_operation_less_eq() {
    RPNCalc test;
    stringstream ss;
    Datum num_1(3);
    Datum num_2(5);
    test.push_datum(num_1);
    test.push_datum(num_2);
    test.stack.print(ss);
    assert(ss.str() == "35");
    ss.str(""); //clear stream
    test.bool_operation("<=");
    test.stack.print(ss);
    assert(ss.str() == "#t");
}

void test_bool_operation_great_eq() {
    RPNCalc test;
    stringstream ss;
    Datum num_1(3);
    Datum num_2(5);
    test.push_datum(num_1);
    test.push_datum(num_2);
    test.stack.print(ss);
    assert(ss.str() == "35");
    ss.str(""); //clear stream
    test.bool_operation(">=");
    test.stack.print(ss);
    assert(ss.str() == "#f");
}

void test_bool_operation_equal_int() {
    RPNCalc test;
    stringstream ss;
    Datum num_1(3);
    Datum num_2(3);
    test.push_datum(num_1);
    test.push_datum(num_2);
    test.stack.print(ss);
    assert(ss.str() == "33");
    ss.str(""); //clear stream
    test.bool_operation("==");
    test.stack.print(ss);
    assert(ss.str() == "#t");
}

void test_bool_operation_equal_bool() {
    RPNCalc test;
    stringstream ss;
    test.push_datum(boolean);
    test.push_datum(boolean);
    test.stack.print(ss);
    assert(ss.str() == "#t#t");
    ss.str(""); //clear stream
    test.bool_operation("==");
    test.stack.print(ss);
    assert(ss.str() == "#t");
}

void test_bool_operation_equal_string() {
    RPNCalc test;
    stringstream ss;
    Datum trial_t("bob");
    test.push_datum(trial_t);
    test.push_datum(text);
    test.stack.print(ss);
    assert(ss.str() == "bobhello");
    ss.str(""); //clear stream
    test.bool_operation("==");
    test.stack.print(ss);
    assert(ss.str() == "#f");
}

void test_bool_operation_diff_typ() {
    RPNCalc test;
    stringstream ss;
    Datum trial_t("bob");
    test.push_datum(trial_t);
    test.push_datum(num);
    test.stack.print(ss);
    assert(ss.str() == "bob2");
    ss.str(""); //clear stream
    test.bool_operation("==");
    test.stack.print(ss);
    assert(ss.str() == "#f");
}

//testing when datum is rstring
void test_exec () {
    RPNCalc test;
    Datum trial_t("{ 4 5 + }");
    test.push_datum(trial_t);
    test.exec("exec");
    assert(test.stack.top().getInt() == 9 );
}

//testing when datum is a not an rstring
void test_exec_notString () {
    RPNCalc test;
    test.push_datum(num);

    bool runtime_error_thrown = false;
   
    std::string error_message = "";

    try {
        test.exec("exec");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "datum_not_rstring");
}

void test_file () {
    RPNCalc test;
    Datum trial_t("{ add.cylc }");
    test.push_datum(trial_t);
    //test.file("file"); //Prints 11 and 20, which is the expected result
}

void test_wrong_file () {
    RPNCalc test;
    Datum trial_t("{ WrongFile }");
    test.push_datum(trial_t);
    //test.file("file"); //"Unable to read WrongFile" is outputted to cerr.
}

void test_file_not_string () {
    RPNCalc test;
    test.push_datum(num);

    bool runtime_error_thrown = false;
   
    std::string error_message = "";

    try {
        test.file("file");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "datum_not_rstring");
}

//test file and if
void test_run_loop_fact () {
    RPNCalc test;
    ifstream infile;
    check_open(infile, "fact.cylc");
    test.run_loop(infile);
    infile.close();
}

//test file and if
void test_run_loop_fib () {
    RPNCalc test;
    ifstream infile;

    check_open(infile, "fib.cylc");
    test.run_loop(infile);
    
    infile.close();
}

