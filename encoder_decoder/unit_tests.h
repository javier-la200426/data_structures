/*
 * unit_tests.h
 *
 * COMP 15 Project 3: Zap
 * 
 * Tests the functions for phase one of the project as well as 
 * the functions in the HuffmanCoder class. These include 
 * the helper functions for encoding and decoding. 
 * The ZapUtil.h is included to be able 
 * to print trees and visualize output on terminal.
 * 
 * Edited by Javier Laveaga (jlavea01) Wednesday, November 15.
 */

#include "phaseOne.h"
#include "ZapUtil.h"
#include "HuffmanTreeNode.h"
#include "HuffmanCoder.h"
#include <cassert>
#include <string>
#include <iostream> 
#include <fstream>
using namespace std;

template<typename streamtype>
void check_open(streamtype &stream, string file_name) {
        stream.open(file_name);
        if (not stream.is_open()) {
                cerr << "Error: could not open file " << file_name << endl;
                exit(EXIT_FAILURE);
        }
 }

//Using phase1
//tested by seeing output of cout 
void test_count_freqs() {
    ifstream infile;
    check_open(infile, "banana.txt");
    count_freqs(infile);
    infile.close();
}

//Using phase1
//tested by seeing output of cout 
void test_count_freq2() {
    ifstream infile;
    check_open(infile, "hi.txt");
    count_freqs(infile);
    infile.close();
}

//Using phase 1 function
//test with figure 1 tree
void test_serialize_tree() {
    HuffmanCoder sample; //to delete tree
    HuffmanTreeNode *figure1tree = makeFigure1Tree('\0'); 
    string serial = serialize_tree(figure1tree);
    assert(serial == "IIILaLbILeLfILcLd");
    sample.delete_tree(figure1tree);

}

//tested with smaller tree
void test_serialize_tree2() {
    HuffmanCoder sample; //to delete tree
    HuffmanTreeNode *tinyTree = new HuffmanTreeNode('\0', 2);
    tinyTree->set_left(new HuffmanTreeNode('a', 1));
    tinyTree->set_right(new HuffmanTreeNode('b', 1));
    string serial = serialize_tree(tinyTree);
    assert(serial == "ILaLb");
    sample.delete_tree(tinyTree);
}

void test_deserialize_tree() {
    HuffmanCoder object1; //to delete tree
    string sample = "IIILaLbILeLfILcLd";
    //from letter to tree
    HuffmanTreeNode *root = object1.deserialize_tree(sample);
    printTree(root, '\0');
    //from tree to letters
    string serial = object1.serialize_tree(root);
    assert(serial == "IIILaLbILeLfILcLd");
    object1.delete_tree(root);
}

void test_deserialize_tree2 () {
    HuffmanCoder object1; //to delete tree
    string sample = "ILaLb";
    HuffmanTreeNode *root = object1.deserialize_tree(sample);
    printTree(root, '\0');
    //from tree to letters
    string serial = object1.serialize_tree(root);
    assert(serial == "ILaLb");
    object1.delete_tree(root);
}

//test deserialize with empty space as one of the characters 
void test_deserialize_tree3 () {
    HuffmanCoder object1; //to delete tree
    string sample = "IL IL La ";
    cout << sample << endl;
    HuffmanTreeNode *root = object1.deserialize_tree(sample);
    printTree(root, '\0');
    //from tree to letters
    string serial = object1.serialize_tree(root);
    object1.delete_tree(root);
}

//TESTING for encode begins
//tested by seeing output of cout 
void test_count_() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "banana.txt");
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    //prints map with counts
    unordered_map<char,int>::const_iterator it;
    for (it = counts.begin(); it != counts.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
}

void test_count2() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "hi.txt");
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    unordered_map<char,int>::const_iterator it;
    for (it = counts.begin(); it != counts.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
}

//tests calling the encoder function with invalid file
void test_encoder_invalid_file() {
    bool runtime_error_thrown = false;
    // var to track any error messages raised
    std::string error_message = "";

    HuffmanCoder sample;
    ifstream infile;
    try {
        sample.encoder("heyaa", "heyaa");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "Unable to open file heyaa");
}


void test_empty_file_encoder() {
    HuffmanCoder sample;
    ifstream infile;
    sample.encoder("JavEmpty.txt", "banana.txt");
}

//tests the delete tree function by delting figure1 tree
void test_delete_tree() {
    HuffmanCoder sample;
    HuffmanTreeNode *figure1tree = makeFigure1Tree('\0'); //nodes of here
    sample.delete_tree(figure1tree);
}

//builds a tree from banana.txt and prints it to cout
void test_build_tree() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "banana.txt");
    //count the counts
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator>
    my_pq;
    HuffmanTreeNode *root = sample.build_tree(my_pq, counts);
    //tests below
    printTree(root, '\0');
    sample.delete_tree(root);
}

//tests that the proper encodings for all the letters in banana.txt are 
//generated
void test_char_encode() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "banana.txt");
    //count the counts
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator>
    my_pq;
    //Encoding B
    HuffmanTreeNode *root = sample.build_tree(my_pq, counts);
    string encodingB = "";
    encodingB = sample.char_encode(root, 'B', encodingB);
    assert(encodingB == "10");
    //Encoding a
    string encodinga = "";
    encodinga = sample.char_encode(root, 'a', encodinga);
    assert(encodinga == "0");
    //Encoding n
    string encodingn = "";
    encodingn = sample.char_encode(root, 'n', encodingn);
    assert(encodingn == "111");
    //Encoding N
    string encodingN = "";
    encodingN = sample.char_encode(root, 'N', encodingN);
    assert(encodingN == "110");
    sample.delete_tree(root); //to prevent valgrind error
}

//test encoding with banana.txt
void test_characters_encode() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "banana.txt");
    //count the counts
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator>
    my_pq;
    //Encoding B
    HuffmanTreeNode *root = sample.build_tree(my_pq, counts);
    unordered_map<char, string> codes = sample.characters_encode(counts, root);
    //Testing here by printing to cout
    unordered_map<char,string>::const_iterator it2;
    for (it2 = codes.begin(); it2 != codes.end(); it2++) {
        //print
        cout << it2->first << ": " << it2->second << endl;
    }  
    sample.delete_tree(root);
}

//tests characters encode with jav.txt. Jav.txt results in a 
// tree that is identical to the figure 1 tree. the table in the spec 
// was compared to the encoding values generated by characters_encode
void test_characters_encode_2() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "jav.txt");
    //count the counts
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator>
    my_pq;
    //build tree
    //Encoding B
    HuffmanTreeNode *root = sample.build_tree(my_pq, counts);
    unordered_map<char, string> codes = sample.characters_encode(counts, root);
    //Testing here by printing to cout
    unordered_map<char,string>::const_iterator it2;
    printTree(root, '\0');
    //printing encodings
    for (it2 = codes.begin(); it2 != codes.end(); it2++) {
        cout << it2->first << ": " << it2->second << endl;
    }  
    sample.delete_tree(root);
}

//Test to see when file contains a single unique character
void test_characters_encode_single() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "Javsingle.txt");
    //count the counts
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator>
    my_pq;
    //Encoding B
    HuffmanTreeNode *root = sample.build_tree(my_pq, counts);
    unordered_map<char, string> codes = sample.characters_encode(counts, root);
    //Testing here by printing to cout
    unordered_map<char,string>::const_iterator it2;
    for (it2 = codes.begin(); it2 != codes.end(); it2++) {
        cout << it2->first << ": " << it2->second << endl;
    }  
    sample.delete_tree(root);
}

void test_encode_text() {
    HuffmanCoder sample;
    ifstream infile;
    check_open(infile, "jav.txt");
    //count the counts
    unordered_map<char, int> counts = sample.count_freqs(infile);
    infile.close();
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator>
    my_pq;
    HuffmanTreeNode *root = sample.build_tree(my_pq, counts);
    unordered_map<char, string> codes = sample.characters_encode(counts, root);
    check_open(infile, "jav.txt"); //open file again
    string encoded_text = sample.encode_text(codes, infile);
    assert(encoded_text == "00100001101101001010101010101111111111");
    infile.close();
    sample.delete_tree(root);
}

//tests decoder with text with spaces in it
void test_decoder1() {
    HuffmanCoder program;
    program.encoder("JavTestErr.txt", "JavAtext.out");
    program.decoder("JavAtext.out", "JavAtext.out");

}

//tests error where encoding did not match Huffman tree
//doesnt pass valgrind because root is not deleted
void test_decoder_unmatch() {
    HuffmanCoder program;
    program.encoder("banana.txt", "Compressed.out");
    BinaryIO sample; 
    //Reading in zap file to get serialized tree and encoded binary string
    pair<string, string> two_strings = sample.readFile("Compressed.out");
    HuffmanTreeNode *root = deserialize_tree(two_strings.first);
    //catch error (right tree, wrong binary code)
    bool runtime_error_thrown = false;
    // var to track any error messages raised
    std::string error_message = "";
    try {
        //pass in wrong number binary tree encoding
        string message = program.decoding(root, two_strings.second + "1");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "Encoding did not match Huffman tree.");
}


