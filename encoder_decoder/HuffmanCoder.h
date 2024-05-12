/*
 * HuffmanCoder.h
 * Javier Laveaga
 * 11/15/2023
 * 
 * CS 15 Project 3: Zap
 * 
 * Purpose: Header file of HuffmanCoder. This defines the class.
 * The HuffmanCoder class implements the main functions involved in
 * the process of zapping or encoding and unzapping or decoding a text file.
 * The program compresses and decompresses text files using the Huffman coding
 * algorithm. It can be run in just two ways: zap or unzap. 
 * Depending on which is used, the zapped or unzapped file is saved in an 
 * output file. 
 * 
 */

#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream> 
#include "HuffmanTreeNode.h"
#include <queue>
#include "BinaryIO.h"
#include <utility>
#include <sstream>
using namespace std;

class HuffmanCoder {
   public:
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);
    
    private:
    void delete_tree(HuffmanTreeNode *root); 
    //decoder helpers
    HuffmanTreeNode *deserialize_tree(const std::string &s);
    HuffmanTreeNode *read_string(istringstream &ss);
    string decoding(HuffmanTreeNode *root, string binary_encoding);
    string single_decoding(HuffmanTreeNode *root, string binary_encoding);
    void save_to_file(string file_name, string message);
    //encoder helpers
    unordered_map<char, int> count_freqs(istream &text);
    void open_check(ifstream &input, string file_name);
    HuffmanTreeNode *build_tree(
        priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
        NodeComparator> my_pq, unordered_map<char, int> counts);
    unordered_map<char, string> characters_encode(unordered_map<char, int>
    counts, HuffmanTreeNode *root);
    string char_encode(HuffmanTreeNode *root, char character, string encoding);
    string encode_text(unordered_map<char, string> codes, istream &text);
    string serialize_tree(HuffmanTreeNode *root);
    bool check_empty(ifstream &infile, string inputFile);
};

#endif