//
//  main.cpp
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/5/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#include <iostream>
#include "BST_Menu.h"
#include "HashTable_Menu.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    char line[128];
    bool inMenu = true;
    
    BinarySearchTree<CompanyObject>* tree1Ptr = buildCompanyTree("techList.txt", 0);
    BinarySearchTree<CompanyObject>* tree2Ptr = buildCompanyTree("techList.txt", 1);
    hashTable<CompanyObject> *hashTable = buildHashTable("techList.txt");
    
    cout << "Welcome to Nasdaq Tech Companies Database, " << endl;
    cout << "you can easily look for the current NAsdaq technology companies' general information, " << endl;
    cout << "like ticker symbol, full name, IPO year, headquartered country, CEO name, subsector." << endl << endl;
    
    while (inMenu) {
        cout << "***Main Menu***\nPlease enter an option (M for menu): ";
        
        cin.getline(line, 127);
        
        if (line[0] == 'M') {
            cout << "Search companies by ticker symbol" << endl;
            cout << "Search companies by IPO date" << endl;
            cout << "Search companies by name" << endl << endl;
            //print 1
            //print 2
            
            
            cout << "Type BST1 for binary seach tree with ticker symbol as key" <<endl;
            cout << "Type BST2 for binary seach tree with IPO date as key" <<endl;
            cout << "Type HASH for hash table" <<endl;
            cout << "Type quit to exit main menu\n" <<endl;
        }
        
        if (strcmp(line, "BST1") == 0) {
            BST_Menu(0,tree1Ptr);
        }
        if(strcmp(line, "BST2") == 0){
            BST_Menu(1,tree2Ptr);
        }
        if(strcmp(line, "HASH") == 0){
            hashTable_Menu(hashTable);
        }
        if (strcmp(line, "QUIT") == 0) {
            cout << "Exiting Main Menu\n" <<endl;
            inMenu = false;
        }
        
    }
    
    delete tree1Ptr;
    delete tree2Ptr;
    delete hashTable;
    
    return 0;
    
}
