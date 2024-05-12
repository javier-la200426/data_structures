/*
 * unit_tests.h
 *
 * COMP 15 Project 4: Gerp
 * 
 * Purpose: To test the stripNonAlphaNum function with various strings
 * and the tree_traverse function which prints out all the file 
 * paths for every file in a given directory. Also tested past versions 
 * of the read_file_mario function as well as the test_to_Lower function.
 * 
 * Edited by Javier Laveaga (jlavea01) and Eva Caro (ecaro01) 
 * Saturday, Dec 11 2023
 */

#include <cassert>
#include <string>
#include <iostream> 
#include <fstream>
#include "stringProcessing.h"
#include "HashT.h"
#include "Gerper.h"
using namespace std;


void test_stripNonAlphaNum () {
    string t1 = "comp";
    string alphat1 = stripNonAlphaNum(t1);
    assert(alphat1 == "comp");  
}

void test_stripNonAlphaNum_2 () {
    string t1 = "$%^&CO(*&MP(*&^%";
    string alphat1 = stripNonAlphaNum(t1);
    assert(alphat1 == "CO(*&MP");  
}

void test_stripNonAlphaNum_3 () {
    string t1 = "$%^&(*&^%";
    string alphat1 = stripNonAlphaNum(t1);
    assert(alphat1 == "");  
}


void test_stripNonAlphaNum_4 () {
    string t1 = "$$c$$";
    string alphat1 = stripNonAlphaNum(t1);
    assert(alphat1 == "c");  
}


//Testing hash
void test_insert_1 () {
    HashT<int> table1;
    table1.insert("hello", 1);
    set <int>::iterator it;
    int filled_index;
    for (it = table1.filled_buckets.begin(); it != table1.filled_buckets.end(); 
        it++) {
        filled_index = *it; 
    }

    string added_string = table1.table[filled_index].front().first;
    int added_int = table1.table[filled_index].front().second;
    assert(added_string == "hello");
    assert(added_int == 1);
}



void test_insert_2 () {
    HashT<int> table1;
    for (int i = 0; i < 10; i++) {
         table1.insert(to_string(i), 1);
    }
    
    set <int>::iterator it;
    int filled_index;
    for (it = table1.filled_buckets.begin(); it != table1.filled_buckets.end();
             it++) {
        filled_index = *it; 
        cout << table1.table[filled_index].front().first;
    }
}


void test_expand() {
    HashT<int> table1(100);
    assert(table1.size_table == 100);

    for (int i = 0; i < 10; i++) {
         table1.insert(to_string(i), 1);
    }
  
    table1.expand();
    
    set <int>::iterator it;
    int filled_index;
    for (it = table1.filled_buckets.begin(); it != table1.filled_buckets.end();
             it++) {
        filled_index = *it;
        cout << table1.table[filled_index].front().first;
    }
    
    assert(table1.size_table == 200);
    assert(table1.table.size() == 200); // underlying vector

}
// To ensure that inseted key value pairs are at correct positions
// based on compression function.
void test_correct_pos() {
    HashT<int> table1(100);
    assert(table1.size_table == 100);

    int index; 
    bool is_correct = false;

    for (int i = 0; i < 10; i++) {
        is_correct = false;
        table1.insert(to_string(i), 1);
        index = table1.compression(to_string(i));
        for (int j = 0; j < (int)table1.table[index].size(); j++) {
            if (table1.table[index][j].first == to_string(i)) {
                is_correct = true;
            }
        }
        assert(is_correct);
    }
}


void test_find_3() {
    HashT<int> table1;
    for (int i = 0; i < 10; i++) {
        table1.insert(to_string(i), i);
        int *v1 = table1.find_mario(to_string(i));
        assert(*v1 == i);
    }
}

//larger set
void test_find_4() {
    bool found;
    HashT<int> table1;
    for (int i = 0; i < 100; i++) {
        found = false;
        table1.insert(to_string(i), i);

        int *v1 = table1.find_mario(to_string(i));
        if (*v1 == i) {
            found = true;
        }
        assert(found);
    }
}


void test_expand_load () {
    HashT<int> table1(100);
    //insert 71 elements see if it expands
    for (int i = 0; i < 72; i++) {
        table1.insert(to_string(i), i);
        if (i == 71) {
            cout << "should expand now (above expanding)" << endl;
        }
    }
}



void test_xpand() {
    HashT<int> table1;
    table1.size_table = 5;
    table1.table.resize(5);

    for (int i = 0; i < 10; i++) {
         table1.insert(to_string(i), 1);
    }
    int filled_index;


    set <int>::iterator it;
    for (it = table1.filled_buckets.begin(); it != table1.filled_buckets.end();
         it++) {
        int filled_index = *it;
        for (int j = 0; j < (int) table1.table[filled_index].size(); j++) {
            cout << table1.table[filled_index][j].first;
        }
    }
}



void test_find() {
    HashT<HashT<set <int>>> table1(100);

    HashT<set <int>> *table2;
    bool found = false;
    table2 = table1.find_mario(to_string(32));
}

//tests tha find returns value
void test_find_2() {
    HashT<HashT<set <int>>> table1(100);

    HashT<set <int>> table2(100);
    set <int> elset;
    elset.insert(5);

    table2.insert("hello" , elset);

    table1.insert(to_string(32), table2);

    HashT<set <int>> *table3;
    bool found = false;
    table3 = table1.find_mario(to_string(32)); //chang to find_og

    set <int> *elotroset;
    bool found2 = false;
    elotroset = table3->find_mario("hello");

    set <int>::iterator it;
    for (it = elotroset->begin(); it != elotroset->end(); it++) {
        cout << "yoqse" << *it;
    }
}

void test_To_Lower () {
    Gerper program;
    string s1 = "HELueYE";

    s1 = program.To_Lower(s1);
    cout << s1 << endl;
}


void test_read_file_eva() {
    Gerper program;
    ifstream infile;
    program.save_files("JavTestDir");
    program.read_files();
}


