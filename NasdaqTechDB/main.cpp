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
            cout << "Type TICKER to search companies by ticker symbol" << endl;
            cout << "Type IPO search companies by IPO date" << endl;
            cout << "Type NAME search companies by name" << endl;
            cout << "Type ALL display all companies sorted by ticker symbol" << endl;
            //cout << "Type NAME search companies by name" << endl << endl;
            cout << "Type quit to exit main menu\n\n" <<endl;
 
            
            
            //cout << "Type BST1 for binary seach tree with ticker symbol as key" <<endl;
            //cout << "Type BST2 for binary seach tree with IPO date as key" <<endl;
            //cout << "Type HASH for hash table" <<endl;
            
        }
        
        if (strcmp(line, "*BST1*") == 0) {
            BST_Menu(0,tree1Ptr);
        }
        if(strcmp(line, "*BST2*") == 0){
            BST_Menu(1,tree2Ptr);
        }
        if(strcmp(line, "*HASH*") == 0){
            hashTable_Menu(hashTable);
        }
        
        if (strcmp(line, "TICKER") == 0) {
            BSTSearchOption(0, tree1Ptr);
        }
        if(strcmp(line, "IPO") == 0){
            BSTSearchOption(1, tree1Ptr);
        }
        if(strcmp(line, "NAME") == 0){
            hashSearchOption(hashTable);
        }
        if(strcmp(line, "ALL") == 0){
            tree1Ptr->inOrder(displayCompany);
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

void searchManager(){
    
}
