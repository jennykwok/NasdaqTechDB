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

void mainMenuManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable);
void insertManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable);
void deleteManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
   
    
    BinarySearchTree<CompanyObject>* tree1Ptr = buildCompanyTree("techList.txt", 0);    // 0: ticker symbol
    BinarySearchTree<CompanyObject>* tree2Ptr = buildCompanyTree("techList.txt", 1);    // 1: IPO
    hashTable<CompanyObject> *hashTable = buildHashTable("techList.txt");               // default: name
    
    cout << "Welcome to Nasdaq Tech Companies Database, " << endl;
    cout << "you can easily look for the current NAsdaq technology companies' general information, " << endl;
    cout << "like ticker symbol, full name, IPO year, headquartered country, CEO name, subsector." << endl << endl;
    
    mainMenuManager(tree1Ptr, tree2Ptr, hashTable);
    
    delete tree1Ptr;
    delete tree2Ptr;
    delete hashTable;
    
    return 0;
    
}

void insertManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable){
    char tickerSymbol[127];
    char companyName[127];
    char IPO_date[127];
    char country[127];
    char CEO[127];
    char subsector[127];
    
    cout << "INSERTING NEW COMPANY (Type CANCLE at any time to go back)" <<endl;
    cout << "\tCompany Name             : ";    cin.getline(companyName, 127); if(strcmp(companyName, "CANCLE") == 0){return;}
    cout << "\tCompany Ticker Symbol    : ";    cin.getline(tickerSymbol, 127); if(strcmp(tickerSymbol,"CANCLE")== 0){return;}
    cout << "\tCompany IPO Date         : ";    cin.getline(IPO_date, 127); IPO_date[8] = '\0'; if(strcmp(IPO_date, "CANCLE") == 0){return;}
    cout << "\tCompany Country          : ";    cin.getline(country, 127); if(strcmp(country, "CANCLE")== 0){return;}
    cout << "\tCompany CEO              : ";    cin.getline(CEO, 127); if(strcmp(CEO, "CANCLE")== 0){return;}
    cout << "\tCompany Subsector        : ";    cin.getline(subsector, 127); if(strcmp(subsector, "CANCLE")== 0){return;}
    
    CompanyObject newCompany = CompanyObject(0,tickerSymbol,companyName,IPO_date,country,CEO,subsector);    // key: ticker symbol
    CompanyObject temp;
    
    if (!treePtr->getEntry(newCompany, temp) || !treePtr2->getEntry(newCompany, temp) || !hashTable->getEntry(hashFunc, newCompany, temp)) {
        treePtr->insert(newCompany);
        newCompany.setKeyNumber(1);         // change key to IPO for tree2
        treePtr2->insert(newCompany);
        newCompany.setKeyNumber(2);         // change key to name for hash table
        hashTable->insertEntry(hashFunc, newCompany);

        cout << companyName << " Succesfully inserted!"<<endl;
    }else{
        cout << "Failed to insert, company already exist in database!" <<endl;
    }
    
   
    
}

// delete by ticker symbol
void deleteManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable){
    
    char line[128];
    cout << "Please enter ticker symbol of company to be deleted : ";
    cin.getline(line, 128);
    CompanyObject toBeDeleted;
    CompanyObject temp = CompanyObject(0, line, "", "", "", "", "");    // Set key = ticker symbol.
    if (treePtr->getEntry(temp, toBeDeleted)) {
        treePtr->remove(toBeDeleted);
        toBeDeleted.setKeyNumber(1);
        treePtr2->remove(toBeDeleted);
        toBeDeleted.setKeyNumber(2);
        hashTable->deleteEntry(hashFunc, toBeDeleted);
        cout << "Succesfully deleted company\n" <<endl;
    }else{
        cout << "Unable to delete company\n" <<endl;
    }
    
    
}

void mainMenuManager(BinarySearchTree<CompanyObject>* tree1Ptr,BinarySearchTree<CompanyObject>* tree2Ptr,hashTable<CompanyObject> *hashTable){
    
    char line[128];
    bool inMenu = true;
    
    while (inMenu) {
        cout << "***Main Menu***\nPlease enter an option (M for menu): ";
        
        cin.getline(line, 127);
        
        if (line[0] == 'M') {
            cout << "Type TICKER to search companies by ticker symbol" << endl;
            cout << "Type IPO search companies by IPO date" << endl;
            cout << "Type NAME search companies by name" << endl;
            cout << "Type ALL display all companies sorted by ticker symbol" << endl;
            cout << "Type INSERT to insert a new company" << endl << endl;
            cout << "Type quit to exit main menu\n\n" <<endl;
            
            
            
            //cout << "Type BST1 for binary seach tree with ticker symbol as key" <<endl;
            //cout << "Type BST2 for binary seach tree with IPO date as key" <<endl;
            //cout << "Type HASH for hash table" <<endl;
            
        }
        
        if (strcmp(line, "*BST1*") == 0) {          // hidden
            BST_Menu(0,tree1Ptr);
        }
        if(strcmp(line, "*BST2*") == 0){            // hidden
            BST_Menu(1,tree2Ptr);
        }
        if(strcmp(line, "*HASH*") == 0){            // hidden
            hashTable_Menu(hashTable);
        }
        
        if (strcmp(line, "TICKER") == 0) {
            BSTSearchOption(0, tree1Ptr);
        }
        if(strcmp(line, "IPO") == 0){
            BSTSearchOption(1, tree2Ptr);
        }
        if(strcmp(line, "NAME") == 0){
            hashSearchOption(hashTable);
        }
        if(strcmp(line, "INSERT") == 0){
            insertManager(tree1Ptr, tree2Ptr, hashTable);
        }
        if(strcmp(line, "DELETE") == 0){
            deleteManager(tree1Ptr, tree2Ptr, hashTable);
        }
        if(strcmp(line, "ALL") == 0){
            tree1Ptr->inOrder(displayCompany);
        }
        
        
        
        if (strcmp(line, "QUIT") == 0) {
            cout << "Exiting Main Menu\n" << endl;
            cout << "Thank you for using our NAsdaq Technology Companies Database." << endl;
            inMenu = false;
        }
        
    }

}

