//
//  HashTable_Menu.cpp
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/9/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#include "HashTable_Menu.h"


/***********************************************
 hashFunc: hash function we create and provide for the
 hashTable template to use with our Company Object.
 Takes in a Company and number of buckets and returns
 an integer reperesenting the bucket to be placed in.
 **********************************************/

int hashFunc(CompanyObject company, int numberOfBuckets){
    int key = 0;
    for (int i = 0; i < company.getCompanyName().length(); i++) {
        //key += (int)front[i] * (int)front[i] * (int)front[i];
        key += (int)company.getCompanyName()[i];
    }
    return (key % numberOfBuckets);
}

void printCompany(CompanyObject company){
    company.displayCompany();
}

void printCompanyIndent(CompanyObject company){
    cout << company.getTickerSymbol() << ", " << company.getCompanyName() << " (" << company.getSubsector() << ") " << endl;
    
}

/***********************************************
 buildHashTable: takes string for filename, reads data from file
 and produces a hashTable with entries propulated from file. All
 entries unable to be inserted due to full buckets are writen to
 rejected txt. Function returns pointer to the hashTable.
 **********************************************/

hashTable<CompanyObject> *buildHashTable(string fileName){
    hashTable<CompanyObject> *hashTable = new ::hashTable<CompanyObject>(31,3);
    
    ifstream inputFile(fileName);
    ofstream rejectedList("rejected.txt");
    
    string tickerSymbol;
    string companyName;
    string IPO_date;
    string country;
    string CEO;
    string subsector;
    
    while (!inputFile.eof()) {
        
        getline(inputFile,tickerSymbol,';');
        getline(inputFile,companyName,';');
        getline(inputFile,IPO_date,';');
        getline(inputFile,country,';');
        getline(inputFile,CEO,';');
        getline(inputFile,subsector);
        
        CompanyObject newCompany = CompanyObject(2,tickerSymbol,companyName,IPO_date,country,CEO,subsector);        // key: Name
        
        if (!hashTable->insertEntry(hashFunc, newCompany)) {        // pass the hashFunc to template function insertEntry.
            cout << "Failed to insert " << companyName << " to hash table!\n" << endl;
            rejectedList << tickerSymbol << " " << companyName << " (" << subsector << ") " << endl;
            rejectedList << CEO << " " << IPO_date << " " << country << "\n" << endl;
            
            // Don't reject any companies.
        }
        
    }
    
    
    inputFile.close();
    rejectedList.close();
    return hashTable;
}


void hashTable_Menu(hashTable<CompanyObject> *hashTable){
    
    cout << "\n***Entering Hash Table Menu***\n"<<endl;
    displayHashTableMenu();
    
    char option;
    char line[128];
    bool inMenu = true;
    
    while (inMenu) {
        
        cout << "Please enter an option (M for menu): ";
        cin.getline(line, 127);
        option = line[0];
        
        switch (option) {
            case 'S':{
                hashSearchOption(hashTable);
                break;
            }
            case 'D':
                cout << "\nAll Entries: \n\n";
                hashTable->printHash(printCompany);
                cout << "\n";
                break;
                
            case 'P':
                hashTable->printHashIndented(printCompanyIndent);
                break;
                
            case 'T':
                hashTable->displayStats();
                break;
                
            case 'M':
                displayHashTableMenu();
                break;
                
            case 'Q':
                inMenu = false;
                cout << "Hash Table Menu Exited!\n\n" <<endl;
                break;
                
            default:
                break;
        }
    }
}

void displayHashTableMenu()
{
    cout << "S – Search by a unique key" <<endl;
    cout << "D – Display list: display the contents of the hash table" <<endl;
    cout << "P – Print the hashed table: show the index and indent synonyms" <<endl;
    cout << "T – Show statistics" <<endl;
    cout << "Q – Quit" <<endl;
}

/***********************************************
 hashSearchOption: takes in an hashSearchOption takes a 
 hashTable and perform search menu. (Sub menu of full hashTable menu)
 **********************************************/

void hashSearchOption(hashTable<CompanyObject> *hashTable){
   
    char companyName[128];
    CompanyObject temp;
        while (1) {
            cout << "Enter company name (QUIT to stop searching): ";
            cin.getline(companyName, 127);
            cout << endl;
            
            if (strcmp(companyName, "QUIT") == 0) {break;}
            if (hashTable->getEntry(hashFunc,CompanyObject(0,"",companyName,"","","",""),temp)){
                printCompany(temp);
                cout << "\n" <<endl;
            }else{
                cout << endl;
            }
    }
   
}
