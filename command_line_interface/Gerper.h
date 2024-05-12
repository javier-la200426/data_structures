/*
 * Gerper.h
 *
 * COMP 15 Project 4: Gerp
 * 
 * Interface for the Gerper class, which is a word-search algorithm
 * for directories of files. It enables near-immediate search, with 
 * the option of case sensitive/insensitive search. It contains a struct
 * which represents hte information of a line. This is stored into 
 * a vector of lines. The data structure responsible for storing the 
 * words is a Hash table which contains a smaller Hash table as its 
 * value. The value of the smaller Hash is a set of integers, which 
 * represents the indices of the line_vector for a particular word.
 * It contains all the functions responsible for indexing files as well 
 * as finding queries.
 * 
 * 
 * Edited by Javier Laveaga (jlavea01) and Eva Caro (ecaro01) Friday, Dec 11.
 */

#ifndef GERPER_H
#define GERPER_H

#include "DirNode.h"
#include "HashT.h"
#include "stringProcessing.h"
#include "FSTree.h"
#include <fstream>
#include <sstream>
using namespace std;

struct line_info {
    string line;
    int line_num; 
    int file_index;
};

class Gerper {
    
public:
    Gerper();
    bool save_files(string directory);
    void traverse_tree(DirNode *curr_node, string path);

    void read_query(ofstream &outstream); 

    void open_check(ifstream &input, string file_name);
    void read_files();

    void print_lines(set<int> *set, ofstream &outstream); 

    string To_Lower(string Capital_Word);
    void read_file_mario(ifstream &input, int file_vect_index, int &line_index);
    void handle_query(string letters2, ofstream &oustream , bool insensitive);
    void store_word(string real_word, string lower_word, int &line_index);
    void handle_run(string letters1, bool &unexpected_eof, ofstream &outstream, 
    bool &run);
    void insensitive_case(HashT<set<int>> *small_table, set<int> *big_set);

private:
    HashT<HashT<set <int>>> table;
    vector<line_info> line_vect;
    vector<string> file_vect;
};

#endif
