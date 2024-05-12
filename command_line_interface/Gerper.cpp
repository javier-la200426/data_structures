/*
 * Gerper.cpp
 *
 * COMP 15 Project 4: Gerp
 * 
 * Implementation of the Gerper class, which is a word-search algorithm
 * for directories of files and utilizes the HashT class. It creates an 
 * index of words appearing in the files by creating a Hash table with
 * a value type of HashT. This allows for near-immediate search, with 
 * the option of case sensitive/insensitive search. Also handles 
 * querying users for words to find in the files.
 * 
 * Edited by Javier Laveaga (jlavea01) and Eva Caro (ecaro01) Friday, Dec 11.
 */

#include "Gerper.h"


/*
 * name:      Gerper
 * purpose:   default constructor to initialize an instance 
              of the Gerper class. Sets the size of the Hash table
              to 700000 (proven efficient for expansion)
 * arguments: N/A
 * returns:   N/A
 * effects:   Initializes an empty Hash table.
 */
Gerper::Gerper() {
    table.set_size(700000);
}

/*
 * name:      save_files
 * purpose:   creates and traverses a tree containing the 
              directory/files information, saving the information
              in the file_info struct vector.
 * arguments: a string containing the name of the directory to save
 * returns:   N/A
 * effects:   Builds a tree of FSTreeNodes and calls the traverse_tree
              function. Catches error in case of empty or single-file
              directory.
 */
bool Gerper::save_files(string directory) {
    bool runtime_error = false;
    std::string error_message = "";
    try { // In case of empty/single-file directory
        FSTree tree(directory); // Building the tree
    } catch (const std::runtime_error &e) {
        runtime_error = true;
        error_message = e.what();
    }
    if (runtime_error) {
        cout << "Could not build index, exiting.\n";
        return true; //meaning tree is empty
    } 
    // Must rebuild because "tree" is out of scope
    FSTree tree_good(directory);
    string path = "";
    traverse_tree(tree_good.getRoot(), path);
    return false;
}

/*
 * name:      traverse_tree
 * purpose:   recursive function to save file path information in the
              file info vector.
 * arguments: a DirNode pointer to the root of the tree to traverse
              and an empty string in which to record the file paths 
              along the recursive calls. 
 * returns:   N/A
 * effects:   saves the file paths in the file_info vector.
 */
void Gerper::traverse_tree(DirNode *curr_node, string path) {
    path += curr_node->getName() + "/"; 
    // If directory has files, store them int he file_info vector
    if (curr_node->hasFiles()) {
        //traverse over files and populate file_vect 
        string file_path;
        string file_name;
        for (int i = 0; i < curr_node->numFiles(); i++) {
            file_path = path + curr_node->getFile(i); 
            file_vect.push_back(file_path);
        }
    }
    // If directory has subdirectories, recurse through them
    if (curr_node->hasSubDir()) {
        // Traverse subdirectories
        for (int i = 0; i < curr_node->numSubDirs(); i++) {
            traverse_tree(curr_node->getSubDir(i), path);
        }
    }
    
}

/*
 * name:      open_check
 * purpose:   ensures files are properly opened
 * arguments: a reference to an ifstream to use to open the file 
              and a string containing the name of the file to open.
 * returns:   N/A
 * effects:   throws a runtime error if file cannot be opened.
 */
void Gerper::open_check(ifstream &input, string file_name) {
    input.open(file_name);
    if (not input.is_open()) {
        throw runtime_error("Unable to open file " + file_name);
    }
}

/*
 * name:      read_files
 * purpose:   opens and reads every file in the given directory,
              storing the contents of the files in a vector of 
              line_info structs.
 * arguments: N/A
 * returns:   N/A
 * effects:   throws a runtime error if file cannot be opened, 
              calls necessary functions open_check and read_file.
 */
void Gerper::read_files() {
    ifstream input;
    int line_index = 0;
    // For every file
    for (int i = 0; i < (int) file_vect.size(); i++) {
        open_check(input, file_vect[i]);
        read_file_mario(input, i, line_index);
        input.close(); 
    }
}

/*
 * name:      read_file_mario
 * purpose:   reads in every line in a given filestream, storing 
              each one in a line_info struct vector, along with 
              its corresponding line number and its corresponding
              index in the file_info vector. Stores the lower_case 
              (stripped of non-alhpanumeric chars) version of each 
              word in the Hash table and the original version (also
              stripped) version in the smaller hash table (the value_type
              of the lower_case key).
 * arguments: a reference to an ifstream to read from, an integer 
              containing the index of the file currently being read in,
              and the address of an integer containing the next unfilled
              slot in the line_info vector.
 * returns:   N/A
 * effects:   adds to the line_info vector, calls helper functions 
              stripNonAlphaNum, To_Lower, and inserts elements into the
              main Hash table and its sub-hash tables.
 */
void Gerper::read_file_mario(ifstream &input, int file_vect_index, 
                            int &line_index) {
    string line_in; // Used to store line contents
    int line_num = 1; // Starting at top of file
    string real_word, lower_word;
    istringstream ss;
    line_info line_info_struct;
    while(getline(input, line_in)) {
        line_info_struct.line = line_in;
        line_info_struct.line_num = line_num;
        line_info_struct.file_index = file_vect_index;
        line_vect.push_back(line_info_struct);
        ss.str(line_in);
        while(ss >> real_word) {
            real_word = stripNonAlphaNum(real_word); //correctly formatted word
            if (real_word != "") { //we do not want to store non alpha words
                lower_word = To_Lower(real_word);
                store_word(real_word, lower_word, line_index);
            } 
        }
        ss.clear();
        line_num++;
        line_index++;
    }
}

/*
 * name:      store_word
 * purpose:   handles storing words in the Hash table
 * arguments: a string containing the real (original) word,
 *            a string containing the lower-case version of the
 *            word, and the address of an int containing the
 *            lindex of the vector at which to continue storing.
 * returns:   N/A
 * effects:   adds to the line_info vector,and inserts elements into the
              main Hash table and its sub-hash tables.
 */
void Gerper::store_word(string real_word, string lower_word, int &line_index) {
    HashT<set <int>> *small_table = table.find_mario(lower_word);
    if (small_table == nullptr) { //if not found in big hash
        HashT<set<int>> small_hash(3); //declare small hash
        set<int> new_set; //declare new set
        new_set.insert(line_index); //insert line_num
        //insert real word and filled set to small hash
        small_hash.insert(real_word, new_set); 
        //insert filled small hash into big hash
        table.insert(lower_word, small_hash); //insert in big hash
    } else { //if it is found in big hash
        //small_table is now the corresponding smaller table
        set<int> *value_set = small_table->find_mario(real_word);
        if (value_set == nullptr) { //if real word is not found in small hash
            //make new key for it (this is a set)
            set<int> new_set2;
            new_set2.insert(line_index); //fill set with line #
            //insert new key value pair into smaller hash table 
            small_table->insert(real_word, new_set2);
        } else { //if it is found in small hash
            value_set->insert(line_index); //fill set with line
        }
    }  
}

/*
 * name:      To_Lower
 * purpose:   converts a string into its lower case version.
 * arguments: a string containing the original word. 
 * returns:   a string containing the lower case version.
 * effects:   N/A
 */
string Gerper::To_Lower(string Capital_Word) {
    string lowercase = "";
    for (int i = 0; i < (int)Capital_Word.length(); i++) {
        lowercase += tolower(Capital_Word[i]);
    }
    return lowercase;
}

/*
 * name:      read_query
 * purpose:   prompts the user for a query from standard input
              and handles the command, finding all instances
              of the inputted word in the provided directory.
 * arguments: a reference to an ofstream to direct output to.
 * returns:   N/A
 * effects:   quits the program if quit command inputted. Changes 
              ofstream if "@f" command provided. Exits the program 
              if an ofstream cannot be opened.
 */
void Gerper::read_query(ofstream &outstream) {
        string letters1;
        bool run = true;
        bool unexpected_eof = false;
        cout << "Query? ";
        while (run and cin >> letters1) {
            handle_run(letters1, unexpected_eof, outstream, run);
            if (not unexpected_eof and run) {
                cout << "Query? ";
            }     
        }
        if (not unexpected_eof) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
        }
}

/*
 * name:      handle_run
 * purpose:   handles all queries
 * arguments: a string containing the word to find in the Hash table,
 *            the address of a boolean that indicates whether the file
 *            ended at an insensitive or file query (@i or @f), a 
 *            reference to the output stream, and the address of a 
 *            boolean that dictates whether to continue running.
 * returns:   N/A
 * effects:   When run is set to false, the while loop in which it
 *            is called will cease.
 */
void Gerper::handle_run(string letters1, bool &unexpected_eof, 
ofstream &outstream, bool &run) {
    string letters2 = "";
    if (letters1 == "@q" or letters1 == "@quit") {
        run = false;
    } else if (letters1 == "@i" or letters1 == "@insensitive" ) {
        cin >> letters2; //this is word
        if (letters2 != "") {
            handle_query(letters2, outstream, true);
        } else {
            cout << "Unexpected EOF\n";
            unexpected_eof = true;
        }
    } else if (letters1 == "@f") {
        cin >> letters2;
        if (letters2 != "") {
            outstream.close();
            outstream.open(letters2);
            if (not outstream.is_open()) {
                cout << "Could not open " << letters2 << endl;
                unexpected_eof = true;
                run = false;
            } 
        } else {
            cout << "Unexpected EOF\n";
            unexpected_eof = true;
        }
    } else { //letters1 is a word (case sensitive)
        handle_query(letters1, outstream, false); 
    }
    
}

/*
 * name:      print_lines
 * purpose:   prints the lines corresponding to the ints in a provided set
 * arguments: a pointer to a set of ints containing the indices of the 
              line_info vector to print and a reference to an ofstream 
              to direct ouput to.
 * returns:   N/A
 * effects:   N/A
 */
void Gerper::print_lines(set<int> *value_set, ofstream &outstream) {
    int file_vect_index;
    set <int>::iterator it;
    for (it = value_set->begin(); it != value_set->end(); it++) {
        file_vect_index = line_vect[*it].file_index;
        outstream << file_vect[file_vect_index] <<
        ":" << line_vect[*it].line_num << ": " << 
        line_vect[*it].line << endl;
    }
}

/*
 * name:      handle_query
 * purpose:   finds case sensitive and insensitive words in the Hash
              table.
 * arguments: a string containing the word to look for, a reference 
              to an ofstream to direct output to, and a bool detailing
              whether to conduct a case insensitive search.
 * returns:   N/A
 * effects:   N/A
 */
void Gerper::handle_query(string letters2, ofstream &outstream, 
                        bool insensitive) {
    string stripped_word = stripNonAlphaNum(letters2);
    bool not_found = false;
    string to_lower_word = To_Lower(stripped_word);
    HashT<set <int>> *small_table = table.find_mario(to_lower_word);
    if (small_table == nullptr) { //not found in big table
        not_found = true;
    } else { //found in big table. (it could or could not be in smaller)
            if (insensitive) {
                set<int> big_set;
                set<int> *big_set_p = &big_set;
                insensitive_case(small_table, big_set_p);
                print_lines(big_set_p, outstream);
            } else {
                set<int> *value_set = small_table->find_mario(stripped_word);
                if (value_set != nullptr) { // If found in smaller table
                    print_lines(value_set, outstream);
                } else {
                    not_found = true;
                }
            }
    }
    if (not_found) {
        if (insensitive) {
            outstream << stripped_word << " Not Found." << endl;
        } else {
            outstream << stripped_word  << 
            " Not Found. Try with @insensitive or @i." << endl;
        }
    }
}

/*
 * name:      insensitive_case
 * purpose:   compiles sets of ints from all variations of a word into
 *            one big set to avoid repetitions.
 * arguments: a pointer to a Hash table (the one containing variations
 *            of words and their corresponding sets of ints) and a 
 *            pointer to a set of ints in which to store all the ints.
 * returns:   N/A
 * effects:   N/A
 */
void Gerper::insensitive_case(HashT<set<int>> *small_table, 
                                set<int> *big_set_p) {
    vector< vector< pair< string, set <int> > > > vector;
    vector = small_table->get_vector();
    set <int> filled_buckets = small_table->get_filled_buckets();
    set <int>::iterator it, it2;
    for (it = filled_buckets.begin(); it != filled_buckets.end(); it++) {
        int filled_index = *it;
        // To ensure no repetition in insensitive case, collect all
        // ints within the sets and put in big set, print_lines on it
        for (int j = 0; j < (int)vector[filled_index].size(); j++) {
            set <int> *individual_set = &vector[filled_index][j].second;
            big_set_p->insert(individual_set->begin(), individual_set->end());
        } 
    }
}
 

