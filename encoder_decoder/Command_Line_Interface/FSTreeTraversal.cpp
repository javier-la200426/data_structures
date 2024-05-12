/*
 * FSTreeTraversal.cpp
 * Javier Laveaga and Eva Caro
 * 12/02/2023
 * 
 * CS 15 Project 4: Gerp
 * 
 * Purpose: Traverses a tree consisting of DirNodes which represent 
 * directories and files, printing out the paths to each file. 
 * Contains the main program and function 
 * declaration and implementation of tree_traverse.
 * 
 */
#include "DirNode.h"
#include "FSTree.h"
#include <string>
#include <iostream>
using namespace std;

void tree_traverse(DirNode *root, string path);

int main(int argc, char *argv[]) {
    if (argc == 2) {
        FSTree tree(argv[1]);
        string path = "";
        tree_traverse(tree.getRoot(), path); 
    } 
}

/*
 * name: tree_traverse
 * purpose: Traverses a tree consisting of DirNodes printing out the 
 * paths to each file
 * arguments: The root of a tree of DirNodes and an empty string in
 * which the path will be built
 * returns: Nothing
 * effects: Prints out to standard output the paths of each file 
 */
void tree_traverse(DirNode *curr_node, string path) {
    path += curr_node->getName() + "/"; 
    //If directory has files, print them
    if (curr_node->hasFiles()) {
        //traverse over files 
        for (int i = 0; i < curr_node->numFiles(); i++) {
            cout << path + curr_node->getFile(i) << endl;
        }
    }
    //if directory has subdirectories, recurse them
    if (curr_node->hasSubDir()) {
        //traverse over subdirs
        for (int i = 0; i < curr_node->numSubDirs(); i++) {
            tree_traverse(curr_node->getSubDir(i), path);
        }
    }
}
