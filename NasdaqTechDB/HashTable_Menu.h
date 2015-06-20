//
//  HashTable_Menu.h
//  NasdaqTechDB
//
//   Description:
//      This is the header file where
//      the actual hash function, search options, menu, display and
//      the input to hashTable functions are added to the abtract hashtable ADT.

#ifndef __NasdaqTechDB__HashTable_Menu__
#define __NasdaqTechDB__HashTable_Menu__

#include <iostream>
#include <string>
#include <fstream>
#include "hashTable.h"
#include "CompanyObject.h"

int hashFunc(CompanyObject company, int numberOfBuckets);
void printCompany(CompanyObject company);
void printCompanyToFile(CompanyObject company, ofstream &outputFile);
void printCompanyIndent(CompanyObject company);
hashTable<CompanyObject> *buildHashTable(string fileName);
void hashTable_Menu(hashTable<CompanyObject> *hashTable);
void hashSearchOption(hashTable<CompanyObject> *hashTable);
void displayHashTableMenu();

#endif /* defined(__NasdaqTechDB__HashTable_Menu__) */
