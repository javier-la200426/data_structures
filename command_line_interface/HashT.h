/*
 * hash.h
 *
 * COMP 15 Project 4: Gerp
 * 
 * Interface of the HashT class. It is responsible for constructing
 * a hash table of a given size as well as insertion, 
 * rehashing/expanding, and finding a value. It uses a vector of vectors 
 * to use chaining. The inner vector contains pairs of strings
 * and a value_types selected by the client. It also has a set of 
 * integers which has the indices of the filled buckets of the outer
 * vector.
 * 
 * Edited by Javier Laveaga (jlavea01) and Eva Caro (ecaro01) Friday, Dec 11.
 */

#ifndef HASHT_H
#define HASHT_H

#include "DirNode.h"
#include <vector>
#include <iostream>
#include <utility> 
#include <functional>
#include <set>

using namespace std;

template <typename value_type>
class HashT {
    
public:

    HashT();
    HashT(int chosen_size);

    void insert(string key, value_type value);
    void expand();
    int compression(string key);
    value_type* find_mario(string key);
    void set_size(int new_size);
    set <int>  get_filled_buckets();
    vector< vector< pair< string, value_type > > > get_vector();

private:

    int size_table;
    int num_elements;
    vector< vector< pair< string, value_type > > > table;
    set <int> filled_buckets;
};



#endif
