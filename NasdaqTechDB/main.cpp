//
//  main.cpp
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/5/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "BST_Menu.h"
#include "HashTable_Menu.h"

using namespace std;

void mainMenuManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable);
void insertManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable);
void deleteManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable);
void searchManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable);
void saveManager(hashTable<CompanyObject> *hashTable);
void displayMainOptions();

int main(int argc, const char * argv[]) {
    
    //Instantiates a pointer to BST and Hashtable and builds the tree/hashtable
    // using the build functions from the repective menu implementation files
    BinarySearchTree<CompanyObject>* tree1Ptr = buildCompanyTree("techList.txt", 0);
    BinarySearchTree<CompanyObject>* tree2Ptr = buildCompanyTree("techList.txt", 1);
    hashTable<CompanyObject> *hashTable = buildHashTable("techList.txt");
    
//    BinarySearchTree<CompanyObject>* tree1Ptr = buildCompanyTree("savedData.txt", 0);
//    BinarySearchTree<CompanyObject>* tree2Ptr = buildCompanyTree("savedData.txt", 1);
//    hashTable<CompanyObject> *hashTable = buildHashTable("savedData.txt");
    
    
    //Display Welcome Screen
    cout << "=========================================================================================================" << endl;
    cout << "|                             Welcome to Nasdaq Technology Companies Database!                          |" << endl;
    cout << "|                            --------------------------------------------------                         |" << endl;
    cout << "|     Easily look through current Nasdaq technology companies' general information. This includes       |" << endl;
    cout << "|     ticker symbol, full name, IPO year, headquartered country, CEO name, and subsector. You can       |" << endl;
    cout << "|     search, display, insert, and delete.                                                              |" << endl;
    cout << "|                                                                                                       |" << endl;
    cout << "|                                      [ENTER] to continue to menu                                      |" << endl;
    cout << "=========================================================================================================" << endl << endl;
    
    //Display the main menu to end user to use database
    mainMenuManager(tree1Ptr, tree2Ptr, hashTable);
    
    //Deallocates all databases
    delete tree1Ptr;
    delete tree2Ptr;
    delete hashTable;
    
    //Thank you Screen
    cout << "\n" << endl;
    cout << "=========================================================================================================" << endl;
    cout << "|                                                                                                       |" << endl;
    cout << "|                       Thank you for using Nasdaq Technology Companies Database! :)                    |" << endl;
    cout << "|                                                                                                       |" << endl;
    cout << "=========================================================================================================" << endl << endl;

    return 0;
    
}

/***********************************************
insertManager: takes in BST1, BST2, and hashtable pointers
 and takes individual input from end user for
 each variable of company object. It creates 
 a new object from user data and inserts it to
 BST1, BST2 and hashtable. Outputs success if 
 insert success and no duplicates/synonyms found.
 **********************************************/
void insertManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable){
    char tickerSymbol[127];
    char companyName[127];
    char IPO_date[127];
    char country[127];
    char CEO[127];
    char subsector[127];
    
    cout << "INSERTING NEW COMPANY (Type CANCEL at any time to go back)" <<endl;
    cout << "\tCompany Name          : ";    cin.getline(companyName, 127); if(strcmp(companyName, "CANCEL") == 0){return;}
    cout << "\tCompany Ticker Symbol : ";    cin.getline(tickerSymbol, 127); if(strcmp(tickerSymbol,"CANCEL")== 0){return;}
    cout << "\tCompany IPO Date      : ";    cin.getline(IPO_date, 127); IPO_date[8] = '\0'; if(strcmp(IPO_date, "CANCEL") == 0){return;}
    cout << "\tCompany Country       : ";    cin.getline(country, 127); if(strcmp(country, "CANCEL")== 0){return;}
    cout << "\tCompany CEO           : ";    cin.getline(CEO, 127); if(strcmp(CEO, "CANCEL")== 0){return;}
    cout << "\tCompany Subsector     : ";    cin.getline(subsector, 127); if(strcmp(subsector, "CANCEL")== 0){return;}
    
    CompanyObject newCompany = CompanyObject(0,tickerSymbol,companyName,IPO_date,country,CEO,subsector);
    CompanyObject temp;
    
    // Checks for any dupulicates/synonyms are found in the existing database
    if (!treePtr->getEntry(newCompany, temp) && !treePtr2->getEntry(newCompany, temp) && !hashTable->getEntry(hashFunc, newCompany, temp)) {
        treePtr->insert(newCompany);
        newCompany.setKeyNumber(1);
        treePtr2->insert(newCompany);
        newCompany.setKeyNumber(2);
        hashTable->insertEntry(hashFunc, newCompany);

        cout << " |" << companyName << " Succesfully inserted.\n\n"<<endl;
    }else{
        cout << "\n |" << "Failed to insert, company already exist in database.\n\n" <<endl;
    }
}

/***********************************************
deleteManager: takes in BST1, BST2, HashTable pointers
 and user input for the ticker symbol of the object
 to delete. Then the object is searched in each 
 database and removed from every database. Outputs
 success if the entry is found and deleted.
 **********************************************/
void deleteManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable){
    
    char line[128];
    cout << "Please enter ticker symbol of company to be deleted: ";
    cin.getline(line, 128);
    CompanyObject toBeDeleted;
    CompanyObject temp = CompanyObject(0, line, "", "", "", "", "");
    if (treePtr->getEntry(temp, toBeDeleted)) {
        treePtr->remove(toBeDeleted);
        toBeDeleted.setKeyNumber(1);
        treePtr2->remove(toBeDeleted);
        toBeDeleted.setKeyNumber(2);
        hashTable->deleteEntry(hashFunc, toBeDeleted);
        cout << " |" << "Succesfully deleted company.\n\n" <<endl;
    }else{
        cout << " |" << "Unable to delete company.\n\n" <<endl;
    }
}


/***********************************************
mainMenuManager: takes in BST1, BST2, HashTable pointers
and uses switch to create main menu for end user to
 interact with all databases in a simple manner.
 **********************************************/
void mainMenuManager(BinarySearchTree<CompanyObject>* tree1Ptr,BinarySearchTree<CompanyObject>* tree2Ptr,hashTable<CompanyObject> *hashTable){
    
    char line[128];
    bool inMenu = true; //bool to exit out of menu loop
    cin.getline(line, 127);
    
    while (inMenu) {
        displayMainOptions(); //prints the menu options in detail
        cout << "Enter Option: ";
        
        cin.getline(line, 127);
        
        
        if (line[0] == 'M') {
            
            
            displayMainOptions();
            
        }
        
        // Developer Options
        
        if (strcmp(line, "*SECRETMENU*") == 0) {
 
            char line[128];
            bool inMenu = true;
            while (inMenu) {
                //developer menu options
                cout << "\n\n------------------------- Developer's Menu ------------------------" << endl;
                cout << " ->  [BST1]      to enter ticker symbol BST menu" << endl;
                cout << " ->  [BST2]      to enter IPO BST menu" << endl;
                cout << " ->  [HASH]      to enter Hash Table menu" << endl;
                cout << " ->  [QUIT]      to exit Developer Menu\n" <<endl;


                cout << "Enter Developer Option: ";
                cin.getline(line, 127);
                
                if (strcmp(line, "BST1") == 0) {
                    BST_Menu(0,tree1Ptr);
                }
                if(strcmp(line, "BST2") == 0){
                    BST_Menu(1,tree2Ptr);
                }
                if(strcmp(line, "HASH") == 0){
                    hashTable_Menu(hashTable);
                }
                if(strcmp(line, "QUIT") == 0){
                    cout << "\n" <<endl;
                    inMenu = false;
                }
            }
        }
        
        // Main options
        
        if(strcmp(line, "SEARCH") == 0){
            searchManager(tree1Ptr, tree2Ptr, hashTable);
        }
        if(strcmp(line, "INSERT") == 0){
            insertManager(tree1Ptr, tree2Ptr, hashTable);
        }
        if(strcmp(line, "DELETE") == 0){
            deleteManager(tree1Ptr, tree2Ptr, hashTable);
        }
        if(strcmp(line, "DISPLAY") == 0){
            tree1Ptr->inOrder(displayCompany);
            cout << "" <<endl;
        }
        if(strcmp(line, "SAVE") == 0){
            saveManager(hashTable);
        }
        if (strcmp(line, "QUIT") == 0) {
            ofstream outputFile("savedData.txt");
            hashTable->printHashToFile(printCompanyToFile, outputFile);
            outputFile.close();
            inMenu = false;
        }
    }
}

/***********************************************
 displayMainOptions: outputs the main menu to user
 **********************************************/
void displayMainOptions(){
    cout << "------------------------ M A I N   M E N U ------------------------" << endl;
    cout << " ->  [SEARCH]    to search for company" << endl;
    cout << " ->  [DISPLAY]   to display all companies sorted by ticker symbol" << endl;
    cout << " ->  [INSERT]    to insert a new company" << endl;
    cout << " ->  [DELETE]    to delete compamy by ticker symbol" << endl;
    cout << " ->  [SAVE]      to save database to specific file" << endl;
    cout << " ->  [QUIT]      to exit main menu\n" <<endl;
}

/***********************************************
 searchManager: takes in BST1, BST2, HashTable
 pointers and either ticker/IPODate/fullname from user
 and search for the company in each respective
 database and display company if found. Otherwise,
 display not found.
 **********************************************/
void searchManager(BinarySearchTree<CompanyObject>* treePtr,BinarySearchTree<CompanyObject>* treePtr2,hashTable<CompanyObject> *hashTable){
    CompanyObject temp; //Temp object to store company data
    char line[128];
    
    while (1) {
    
        cout << "Enter company Ticker Symbol, IPO date, or name to search (Q to exit): ";
        cin.getline(line, 127);
        if (strcmp(line, "Q") == 0) {break;}
        
        if (treePtr->getEntry(CompanyObject(0,line,line,line,"","",""), temp)) {
            displayCompany(temp);
        }else if(treePtr2->getEntry(CompanyObject(1,line,line,line,"","",""), temp)){
            displayCompany(temp);
        }else if(hashTable->getEntry(hashFunc,CompanyObject(2,line,line,line,"","",""), temp)){
            displayCompany(temp);
        }else{
            cout << " |" << "Cound not find company.\n\n" <<endl;
        }

    }
    
    cout << "\n" <<endl;
}

/***********************************************
 SaveManager: takes in hashTable pointer
 and gets a filename from user. It generates an
 output file of that specified name and calls
 printHashToFile function to output to file.
 After finished, it prints success.
 **********************************************/
void saveManager(hashTable<CompanyObject> *hashTable){
    
    char line[128];
    cout << "Enter name of file to save the database to: ";
    cin.getline(line, 127);
    ofstream outputFile(line);
    hashTable->printHashToFile(printCompanyToFile, outputFile);
    outputFile.close();
    cout << " |" << "Saved Database to " << line << "\n\n" << endl;
    
}


