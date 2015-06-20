//
//  HashTable_Menu.cpp
//  NasdaqTechDB
//
//   Description:
//      This is the implementation file for HashTable_Menu.h where
//      the actual hash function, search options, menu, display and
//      the input to hashTable functions are implemented.

#include "HashTable_Menu.h"


/***********************************************
 hashFunc: hash function we create and provide for the
 hashTable template to use with our Company Object.
 Takes in a CompanyObject and number of buckets and returns
 an integer reperesenting the bucket to be placed in.
 **********************************************/

int hashFunc(CompanyObject company, int numberOfBuckets){
    int key = 0;
    for (int i = 0; i < company.getCompanyName().length(); i++) {
        key += (int)company.getCompanyName()[i] + 6;
    }
    
    return (key % numberOfBuckets);
    
}

/***********************************************
printCompany: Calls the display company function
of the company class taken in as an argument
to print the company data
out to console usual fulfilling the user request
for such data
 **********************************************/
void printCompany(CompanyObject company){
    company.displayCompany();
}

/***********************************************
printCompanyToFile: takes in a company object
 and the ofstream object as reference and
 outputs to file each variable of company object
 in a comma separated format
 **********************************************/
void printCompanyToFile(CompanyObject company, ofstream &outputFile){
    outputFile << company.getTickerSymbol() << ";" << company.getCompanyName() << ";" << company.getIPO_date() << ";"
               << company.getCountry() << ";" <<company.getCEO() << ";" << company.getSubsector() << endl;
}

/***********************************************
 printCompanyIndent: Takes ina company object
 and prints to the console the company info 
 in a formatted way for the end user
 **********************************************/
void printCompanyIndent(CompanyObject company){
    cout << company.getTickerSymbol() << ", " << company.getCompanyName() << " (" << company.getSubsector() << ") " << endl;
    
}

/***********************************************
 buildHashTable: takes string for filename, reads data from file
 and produces a hashTable with entries propulated from file. All
 entries unable to be inserted due to full buckets are inserted in
 the subsequent bucket.
 Function returns pointer to the hashTable.
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
        
        CompanyObject newCompany = CompanyObject(2,tickerSymbol,companyName,IPO_date,country,CEO,subsector);
        
        if (!hashTable->insertEntry(hashFunc, newCompany)) {
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


/***********************************************
hashTable_Menu: Take in the company Hashatable pointer
 and uses the switch to create dev menu for the end user to interact
 and to use to get various information offered 
 by the NASDAQ program
 **********************************************/
void hashTable_Menu(hashTable<CompanyObject> *hashTable){
    
    cout << "\n\n------------------- Entering Hash Table Menu ----------------------"<<endl;
    displayHashTableMenu(); //prints the full menu
    
    char option;
    char line[128];
    bool inMenu = true; //bool to exit out of menu loop
    
    while (inMenu) {
        
        cout << "\nEnter option: ";
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
                cout << "Hash Table Menu Exited!" <<endl;
                break;
                
            default:
                break;
        }
    }
}

/***********************************************
 displayHashTableMenu: outputs the menu to user
 **********************************************/
void displayHashTableMenu()
{
    cout << "S – Search by a unique key" <<endl;
    cout << "D – Display list: display the contents of the hash table" <<endl;
    cout << "P – Print the hashed table: show the index and indent synonyms" <<endl;
    cout << "T – Show statistics" <<endl;
    cout << "Q – Quit" <<endl;
}

/***********************************************
 hashSearchOption: takes in an hashtable pointer
 hashSearchOption takes a hashTable and perform search menu. 
 (Sub menu of full hashTable menu)
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
