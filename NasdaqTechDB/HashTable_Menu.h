//
//  HashTable_Menu.h
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/9/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#ifndef __NasdaqTechDB__HashTable_Menu__
#define __NasdaqTechDB__HashTable_Menu__

#include <iostream>
#include <string>
#include <fstream>
#include "hashTable.h"
#include "CompanyObject.h"

int hashFunc(CompanyObject company, int numberOfBuckets);
void printCompany(CompanyObject company);
void printCompanyIndent(CompanyObject company);
hashTable<CompanyObject> *buildHashTable(string fileName);
void hashTable_Menu(hashTable<CompanyObject> *hashTable);

#endif /* defined(__NasdaqTechDB__HashTable_Menu__) */
