/*
 * HuffmanCoder.cpp
 * Javier Laveaga
 * 11/15/2023
 * 
 * CS 15 Project 3: Zap
 * 
 * Purpose: To implement the HuffmanCoder class. This implementation
 * is achieved through the use of two main functions, encoder and
 * decoder, which zap or unzap a file. The encoding process is carried out 
 * by helper functions that take care of opening the file, counting the 
 * frequencies of each character in the text, building a tree using
 * the Huffman algorithm, using the tree to generate character encodings,
 * using the codings to encode the text in binary, serializing the 
 * Huffman tree, and finally saving the serialized tree and text in 
 * a file.
 * The decoding process is taken care of by the helper functions that
 * that read in a zapped file, deserialize the tree, decode the binary 
 * string into ASCII text, and finally save the text to an output file.
 * 
 */


#include "HuffmanCoder.h"

/*
 * name: decoder 
 * purpose: To decompress a previously zapped file and saving the resulting 
 * ASCII text to an output file.
 * arguments: A commpressed input file and an output file write the text to 
 * returns: Nothing
 * effects: Allocates memory by building a new tree and builds the ASCII 
 * message by reading the binary encoded string. Deallocates memory of 
 * tree created. 
 */
void HuffmanCoder::decoder(const std::string &inputFile, 
                        const std::string &outputFile) {
    //output file in this case is the actual text 
    BinaryIO sample; 
    //Reading in zap file to get serialized tree and encoded binary string
    pair<string, string> two_strings = sample.readFile(inputFile);
    //first is serialized tree and second is binary string encoding
    //Deserializing the Tree
    HuffmanTreeNode *root = deserialize_tree(two_strings.first);
    string message = "";
    if (root->isLeaf()) { //if you have a single unique character
        message = single_decoding(root, two_strings.second);
    } else {
        message = decoding(root, two_strings.second);
    }
    save_to_file(outputFile, message);
    delete_tree(root);
}

/*
 * name: save_to_file
 * purpose: To save an ASCII text to an output file.
 * arguments: The name of the file to write to and the ASCII text or message
 * returns: Nothing
 * effects: Saves the text to the output file. Throws error if output file 
 * cannot be opened.
 */
void HuffmanCoder::save_to_file(string file_name, string message) {
    ofstream output;
    output.open(file_name);
        if (not output.is_open()) {
            throw runtime_error("Unable to open file " + file_name);
        }
    output << message;
    output.close();
}

/*
 * name: single_decoding
 * purpose: To decode a binary string encoding with only a single
 * character in the its Huffman tree.
 * arguments: The root the Huffman tree of the binary encoding.
 * returns: Returns the ASCII text decoded form the binary encoding
 * effects: Builds the decoded message or text
 */
string HuffmanCoder::single_decoding(HuffmanTreeNode *root, 
                    string binary_encoding) {
    string message = "";
    char single_char = root->get_val();
    int encoding_length = binary_encoding.length();
    for (int i = 0; i < encoding_length; i++) {
        message += single_char; //append to back of message
    }
    return message;
}

/*
 * name: decoding
 * purpose: To decode a binary string into an ASCII text with more than 
 * a single unique character using a Huffman tree
 * arguments: The root to the tree, and a string representing the binary 
 * encoding.
 * returns: the ASCII text decoded form the binary encoding
 * effects: Traverses the tree as it reads from the binary encoding and
 * throws an error if the encoding did not match the Huffman tree / last node
 * is not a leaf.
 */
string HuffmanCoder::decoding(HuffmanTreeNode *root, string binary_encoding) {
    //
    string message = "";
    int encoding_length = binary_encoding.length();
    HuffmanTreeNode *curr_node = root;
    for (int i = 0; i < encoding_length; i++) {
        //if last node is a not a leaf, then throw error
        char curr_num = binary_encoding[i];
        if (curr_num == '0') { //move left
            curr_node = curr_node->get_left();
        } else if (curr_num == '1') { //move right
            curr_node = curr_node->get_right();
        }
        if ((i == encoding_length - 1) and not curr_node->isLeaf()) {
                throw runtime_error("Encoding did not match Huffman tree.");
        }
        if (curr_node->isLeaf()) {
            //more time efficient
            message += curr_node->get_val(); //append to back of message
            curr_node = root;
        }
    }
    return message;
}

/*
 * name: deserialize_tree 
 * purpose: to transforme a serialized tree string into a Huffman tree
 * arguments: a string representation of a serialized tree
 * returns: a pointer to the root of the Huffman tree
 * effects: allocates memory in the heap for new nodes
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree(const std::string &s) {
    istringstream ss;
    ss.str(s);
    HuffmanTreeNode *root = read_string(ss);
    return root;
}

/*
 * name: read_string
 * purpose: to recursively create a Huffman tree from 
 * a string stream representing the serialized Huffman tree.
 * arguments: a string stream containing the serialized Huffman tree
 * returns: A pointer to the roof of the newly created Huffman tree
 * effects: It allocates new memory for the internal and leaf nodes of the tree
 */
HuffmanTreeNode* HuffmanCoder::read_string(istringstream &ss) {
    char curr_char;
    ss.get(curr_char); 

    if (curr_char == 'I') {
        HuffmanTreeNode *i_node = new HuffmanTreeNode('\0', -1);
        i_node->set_left(read_string(ss));
        i_node->set_right(read_string(ss));
        return i_node; //to set the internal nodes to be children of previous
    } else if (curr_char == 'L') {
        ss.get(curr_char); 
        HuffmanTreeNode *leaf = new HuffmanTreeNode(curr_char, -1);
        return leaf; //to set leaf node to be children of previous
    } else { //if non of the valid options, or string
        return nullptr; 
    }
}

/*
 * name: encoder
 * purpose: To encode a given ASCII text file into compressed binary code
 * arguments: An input file with the ASCII text and the output file in which 
 * the zapped binary file will be saved.
 * returns: Nothing
 * effects: Throws an error if the input file cannot be opened. Prints
 * message to screen if file is empty. Allocates and deallocates memory for the 
 * huffman tree used to generate the encodings.
 */
void HuffmanCoder::encoder(const std::string &inputFile, 
                        const std::string &outputFile) {
    ifstream infile;
    open_check(infile, inputFile); //check if you can open file
    bool is_empty = check_empty(infile, inputFile); //check if file is empty
    if(not is_empty) {
        infile.close(); //close stream
        open_check(infile, inputFile); //open again
        //pass file stream to  to count function
        unordered_map<char, int> counts= count_freqs(infile);
        infile.close();
        //build tree
        priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
        NodeComparator> my_pq;
        HuffmanTreeNode *root = build_tree(my_pq, counts);
        //Generate character encodings
        unordered_map<char, string> codes = characters_encode(counts, root);  
        open_check(infile, inputFile); //open again
        //encode the text
        string encoded_text = encode_text(codes, infile);
        string serial_tree = serialize_tree(root);
        //save serialize tree and encoded text to file
        BinaryIO sample; //declare object
        sample.writeFile(outputFile, serial_tree, encoded_text);
        int text_length = encoded_text.length();
        cout << "Success! Encoded given text using " + to_string(text_length) 
        + " bits." << endl;
        delete_tree(root);
    }
}

/*
 * name: check_empty
 * purpose: To check if an input file is empty
 * arguments: An address to an input file stream and the name of the input file
 * returns: A boolean indicating whether the input file is empty
 * effects: If file is empty, it rints an error message to stdout saying that
 * the file is empty
 */
bool HuffmanCoder::check_empty(ifstream &infile, string inputFile) {
    //check to see if file is empty
    bool is_empty = false;
    char curr;
    infile.get(curr);
    if(infile.eof()) {
        cout << inputFile + " is empty and cannot be compressed." << endl;
        is_empty = true;
    } 
    return is_empty;
}

/*
 * name: delete_tree
 * purpose: To delete a Huffman tree (created by buildtree or deserialization)
 * arguments: The root of a Huffman tree
 * returns: Nothing
 * effects: Deallocates memory in the heap by deleting the tree with a 
 * post order traversal.
 */
void HuffmanCoder::delete_tree(HuffmanTreeNode *root) {
    if (root != nullptr) {
        delete_tree(root->get_left());
        delete_tree(root->get_right());
        delete root;
    }
}

/*
 * name: serialize_tree
 * purpose: To change a Huffman tree to its serialized version
 * arguments: a pointer to the root of a Huffman tree
 * returns: a string containing the serialized version of the tree
 * effects: concatenates string by performing a preorder traversal
 */
string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
    //if empty tree
    if (root == nullptr) {
        return "";
    }
    //if it is a leaf node
    if (root->isLeaf()) {
        return string("L") + root->get_val(); 
        //so that string correctly concatenates.
    }
    //if it is a internal node
    return "I" + serialize_tree(root->get_left()) + 
    serialize_tree(root->get_right());
}

/*
 * name: encode_text
 * purpose: To encode a ASCII text file with binary text using the encodings
 * generated.
 * arguments: An unordered map containing the encodings (codes) for each 
 * of the characters and an input file stream with the ASCII text
 * returns: A string containing the encoded binary text
 * effects: Appends to the back of the encoded text string
 */
string HuffmanCoder::encode_text(unordered_map<char, string> codes, 
                                istream &text) {
    char curr;
    string encoded_text = "";
    text.get(curr);
    //for each character in the text, find where that character
    // is in the codes map. Then add its encoding to the encoded_text string
    while(not(text.eof())) {
        unordered_map<char,string>::const_iterator it = codes.find(curr);
        encoded_text += it->second;
        text.get(curr);
    }
    return encoded_text;
}

/*
 * name: characters_encode
 * purpose: To generate encodings for each of the characters in the ASCII text
 * arguments: An unordered map containing the each of the characters and their
 * counts (not used here). The root of a Huffman tree containing each of the 
 * characters as leafs.
 * returns: an unordered map containing the characters and their corresponding
 * encodings
 * effects: builds an encoding for each character based on the tree. 
 */
unordered_map<char, string> HuffmanCoder::characters_encode(unordered_map<char, 
int> counts, HuffmanTreeNode *root) {
    unordered_map<char, string> codes;
    //iterate over characters in the count map
    unordered_map<char,int>::const_iterator it;
    for (it = counts.begin(); it != counts.end(); it++) {
        char curr_char = it->first; //a character in the count map
        string curr_encoding = ""; //resetting encoding 
        curr_encoding = char_encode(root, curr_char, curr_encoding);
        if (curr_encoding == "") { //if there is only a single unique character
            curr_encoding = "0";
        }
        //store character and encodingin a map of codes
        codes [curr_char] = curr_encoding;
    }
    return codes;
}

/*
 * name: char_encode
 * purpose: To recusively traverse the tree, and, when it finds the desired
 * individual character, it returns a string containing its encoding.
 * arguments: The roof of a Huffman tree, the desired character to find, and 
 * the string encoding initialized to the empty string.
 * returns: a string containing the encoding for an individual character
 * effects: Recursively traverses tree and adds 0s and 1s to the resulting 
 * string based on whether it traverses left or right.
 */
string HuffmanCoder::char_encode(HuffmanTreeNode *root, char character, 
                                string encoding) {
    
    if (root->get_val() == character) { //if you are desired character
       return encoding; //return that encoding
    } else if (root->isLeaf()) { //if you are leaf but not desired character
       return ""; //erase encoding
    } else { // if you are internal node
       //
       return char_encode(root->get_left(), character, encoding + "0") + 
       char_encode(root->get_right(), character, encoding + "1");
    }
}

/*
 * name: build_tree
 * purpose: To build a tree according to the frequencies of each character
 * in an ASCII text (using Huffman algorithm).
 * arguments: An initialized priority queue which will contain Huffman tree 
 * nodes and a comparator node function which compares their frequencies. 
 * returns: The root of the newly created Huffman tree.
 * effects: Allocates memory for the leaf and parent nodes in the tree
 */
HuffmanTreeNode* HuffmanCoder::build_tree(
        priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
        NodeComparator> my_pq, unordered_map<char, int> counts) {

    unordered_map<char,int>::const_iterator it;
    //For each character in counts map, create a node and insert it in my_pq
    for (it = counts.begin(); it != counts.end(); it++) {
        HuffmanTreeNode *curr_leaf = new HuffmanTreeNode(it->first, it->second);
        my_pq.push(curr_leaf);
    }
    //now we have queue with leafs ordered from lowest freq to highest freq
    //Until a single tree remains, pick 2 min freq nodes and
    //join them together with a parent node that stores the sum 
    while(my_pq.size() != 1) { //condition: until single tree remains
        HuffmanTreeNode *child1 = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *child2 = my_pq.top();
        my_pq.pop();
        //\0 is internal node value
        int sum = child1->get_freq() + child2->get_freq();
        HuffmanTreeNode *parent = new HuffmanTreeNode('\0', sum);
        parent->set_left(child1);
        parent->set_right(child2);
        my_pq.push(parent);
    }
    //Popping last element will get the root
    return my_pq.top();
}

/*
 * name: count_freqs
 * purpose: to count the frequencies of each character in the ASCII text and 
 * store the counts in an unordered map
 * arguments: An input file stream containing the ASCII text
 * returns: An unordered map of the characters in the text and their counts
 * effects: fills up the counts map
 */
unordered_map<char, int> HuffmanCoder::count_freqs(std::istream &text) {
    unordered_map<char, int> counts;
    char curr;
    text.get(curr);
    while(not(text.eof())) {
        //if current character not in map, inserit it and set count to 1
        unordered_map<char,int>::const_iterator it = counts.find(curr);
        if (it == counts.end()) { //if not found, it returns counts.end()
            counts [curr] = 1;
        } else { //if it is in map, increment count by 1
            counts [curr] ++;
        }
        text.get(curr);
    }
   return counts;
}

/*
 * name: open_check
 * purpose: To check if an input file can be opened (called in encode function)
 * arguments: An input file stream and the filename with the ASCII text
 * returns: Nothing
 * effects: Throws an error if the file cannot be opened .
 */
void HuffmanCoder::open_check(ifstream &input, string file_name) {
    input.open(file_name);
        if (not input.is_open()) {
            throw runtime_error("Unable to open file " + file_name);
        }
}

