/*
 * hash.cpp
 *
 * COMP 15 Project 4: Gerp
 * 
 * Implementation of the HashT class. This class implements a
 * hash table with keys of type string and uses a template for the 
 * value_type. It accomodates for collisions through chaining. This
 * is achieved by using a vector of vectors to implement the hash 
 * table. It is responsible for constructing a hash table of a given 
 * size as well as insertion, rehashing/expanding, and finding a value
 * associated with a key.
 * 
 * Edited by Javier Laveaga (jlavea01) and Eva Caro (ecaro01) Friday, Dec 11.
 */

#include "HashT.h"

/*
 * name:      HashT
 * purpose:   Default constructor for the HashT class.
 * arguments: N/A
 * returns:   N/A
 * effects:   initializes the underlying vector to a size of 1.
 */
template <typename value_type>
HashT<value_type>::HashT() {
    num_elements = 0;
    size_table = 1;
    table.resize(1);
    
}

/*
 * name:      HashT
 * purpose:   Constructor for HashT class that sets the size of the
              underlying vector to a given chosen_size.
 * arguments: An int containing the size to make the vector
 * returns:   N/A
 * effects:   initializes the underlying vector to a given size.
 */
template <typename value_type>
HashT<value_type>::HashT(int chosen_size) {
    num_elements = 0;
    set_size(chosen_size); //added 
    
}

/*
 * name:      insert
 * purpose:   inserts a given key and value pair into the Hash table.
 * arguments: a string containing the key and a variable of type 
              value_type (utilizing a template) containing the value 
              to insert. 
 * returns:   N/A
 * effects:   expands the Hash table if load factor reaches 0.7.
              Uses chaining to handle collisions.
 */
template <typename value_type>
void HashT<value_type>::insert(string key, value_type value) {
    //float used so that load factor is a decimal
    double load_factor = ((float)num_elements / (float)size_table); 
    if (load_factor >= 0.70) {
        expand();
    }
    int index = compression(key);
    pair<string, value_type> pair1;
    pair1.first = key;
    pair1.second = value;
    table[index].push_back(pair1);
    filled_buckets.insert(index);
    num_elements++;
}

/*
 * name:      compression
 * purpose:   calculates the appropriate index position for a
              given key for insertion into the Hash table.
 * arguments: a string containing the key to insert.
 * returns:   an int containing the index.
 * effects:   mods by table_size to ensure proper index.
 */
template <typename value_type>
int HashT<value_type>::compression(string key) {
    int index = hash<string> {} (key) % size_table;
    return index;
}

/*
 * name:      expand
 * purpose:   expands the size of the Hash table, re-sizing 
              the underlying vector and putting the key-value
              pairs in their new positions based on the new 
              size.
 * arguments: N/A
 * returns:   N/A
 * effects:   changes the index of potentially all the key-value
              pairs and doubles table size.
 */
template <typename value_type>
void HashT<value_type>::expand() {
    int new_size = size_table * 2; 
    vector< vector< pair< string, value_type > > > table2;
    table2.resize(new_size);
    size_table = new_size; //so that compression function mods by new size
    int new_index;
    set <int> new_filled_buckets;
    set <int>::iterator it;
    // For all buckets with elements in them
    for (it = filled_buckets.begin(); it != filled_buckets.end(); it++) {
        int filled_index = *it;
        int bucket_size = table[filled_index].size();
        for (int j = 0; j < bucket_size; j++) {
            // Adding all pairs in bucket to new hash table
            new_index = compression(table[filled_index].back().first);
            new_filled_buckets.insert(new_index);
            pair<string, value_type> temp;
            temp = table[filled_index].back(); //save pair
            table[filled_index].pop_back(); //pop pair
            table2[new_index].push_back(temp);
        }
    }
    filled_buckets = new_filled_buckets; 
    table = table2;
}

/*
 * name:      find_mario
 * purpose:   finds the value associated with a given pair
              using the compression function.
 * arguments: a string containing the key to find.
 * returns:   a value_type variable containing the value
              paired with a certain key.
 * effects:   returns a nullptr if key does not exist in 
              the table.
 */
template <typename value_type>
value_type* HashT<value_type>::find_mario(string key) {
    int index = compression(key);
    for (int i = 0; i < (int) table[index].size(); i++) {
        if (table[index][i].first == key) {
            return &table[index][i].second;
        }
    }
    // if not found return nullptr
    return nullptr;    
}

/*
 * name:      set_size
 * purpose:   sets the size of the vector to a given value.
 * arguments: an int containing the size to make the vector.
 * returns:   N/A
 * effects:   resizes the vector.
 */
template <typename value_type>
void HashT<value_type>::set_size(int new_size) {
    size_table = new_size;
    table.resize(new_size);
}

/*
 * name:      get_filled_buckets
 * purpose:   getter function that returns the filled_buckets
              set of integers (which contains the indices of 
              filled buckets in the hash table).
 * arguments: N/A
 * returns:   the filled_buckets set of integers.
 * effects:   N/A
 */
template <typename value_type>
set <int>  HashT<value_type>::get_filled_buckets() {
    return filled_buckets;
}

/*
 * name:      get_vector
 * purpose:   getter function that returns the underlying vector.
 * arguments: N/A
 * returns:   the hash table's underlying vector.
 * effects:   N/A
 */
template <typename value_type>
vector< vector< pair< string, value_type > > > HashT<value_type>::get_vector() {
    return table;
}

template class HashT<int>; //this is for unittests
template class HashT<HashT<set <int>>>; 
template class HashT<set <int>>; 
template class std::vector<HashT<set <int>>>; 


