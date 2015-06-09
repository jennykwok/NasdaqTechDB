//
//  hashTable.h
//  HW5
//
//  Created by Jenny Kwok on 5/29/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#ifndef __HW5__hashTable__
#define __HW5__hashTable__

#include <stdio.h>
#include <iostream>
#include "hashEntry.h"

using namespace std;

template <class T>
class hashTable {
    
private:
    int numberOfBuckets;
    int BucketSize;
    int bucketsTaken;
    int count;
    int collisions;
    int failedInserts;
    hashEntry<T> **table;
    
    
public:
    //Constructors
    hashTable();
    hashTable(int numberOfBuckets, int BucketSize);
    
    //Destructors
    ~hashTable();
    
    bool getEntry(int hashFunc(T item, int numberOfBuckets),T item, T & foundItem);
    bool insertEntry(int hashFunc(T  newEntry,int numberOfBuckets), const T & newEntry);
    bool deleteEntry(int hashFunc(T entry,int numberOfBuckets), T entry);
    void printHashIndented(void printEntry(T entry));
    void printHash(void printEntry(T entry));
    void displayStats();
};

/***********************************************
 hashTable: constructor, initializes an empty hashTable
 with by defualt 10 buckets of size 3.
 **********************************************/

template <class T>
hashTable<T>::hashTable(){
    numberOfBuckets = 10;
    BucketSize = 3;
    bucketsTaken = 0;
    count = 0;
    collisions = 0;
    failedInserts = 0;
    table = new hashEntry<T>*[numberOfBuckets*BucketSize];
}

/***********************************************
 hashTable: constructor takes in two integers one for
 number of buckets and other for bucket size. Initializes
 hashTable of depending on input sizes.
 **********************************************/

template <class T>
hashTable<T>::hashTable(int numberOfBuckets, int BucketSize){
    this->numberOfBuckets = numberOfBuckets;
    this->BucketSize = BucketSize;
    bucketsTaken = 0;
    count = 0;
    collisions = 0;
    failedInserts = 0;
    table = new hashEntry<T>*[numberOfBuckets*BucketSize];
}

/***********************************************
 insertEntry: takes in a hash function, and object.
 Uses hashFunction to insert object into hashTable, returns
 true if successful, else returns false.
 **********************************************/


template <class T>
bool hashTable<T>::insertEntry(int hashFunc(T newEntry,int numberOfBuckets),const T & newEntry) {
    
    int address = hashFunc(newEntry,numberOfBuckets);
    if (table[address*BucketSize] != NULL) {collisions++;}
    
    for(int i = 0; i < numberOfBuckets; i++){
        int addressLooper = (address + i)%numberOfBuckets;
        
        for (int i = 0; i < BucketSize; i++) {
            if (table[addressLooper*BucketSize +i] == NULL) {
                table[addressLooper*BucketSize +i] = new hashEntry<T>(hashFunc,newEntry,numberOfBuckets);
                if(i == 0){bucketsTaken++;}
                count++;
                return true;
            }
        }
        
    }
    
    
    failedInserts++;
    cout << "Failed to insert\n" <<endl;
    return false;
}

/***********************************************
 deleteEntry: takes in a hash function and object,
 searches hash table for object, if found object in
 hash table is deleted and returns true, else returns false.
 **********************************************/

template <class T>
bool hashTable<T>::deleteEntry(int hashFunc(T entry,int numberOfBuckets), T entry) {
    int address = hashFunc(entry,numberOfBuckets);
    
    for(int i = 0; i < numberOfBuckets; i++){
        int addressLooper = (address + i)%numberOfBuckets;
        
        for (int i = 0; i < BucketSize; i++) {
            if (table[addressLooper*BucketSize +i] != NULL) {
                if (*table[addressLooper*BucketSize + i] == entry) {
                    delete table[addressLooper*BucketSize + 1];
                    return true;
                }
            }
        }
        
    }
    
    printf("Failed to delete entery, entry not found!\n",address);
    return false;
    
}

/***********************************************
 getEntry: takes in hash function, object, and address
 of an object to hold search result. Searches hash table
 for object if found, object is save into foundObject and
 returns true; else returns false;
 **********************************************/

template <class T>
bool hashTable<T>::getEntry(int hashFunc(T entry,int numberOfBuckets), T entry, T & foundItem) {
    int address = hashFunc(entry,numberOfBuckets);
    
    for(int i = 0; i < numberOfBuckets; i++){
        int addressLooper = (address + i)%numberOfBuckets;
        
        for (int i = 0; i < BucketSize; i++) {
            if (table[addressLooper*BucketSize +i] != NULL) {
                if (table[addressLooper*BucketSize + i]->getItem() == entry) {
                    foundItem = table[addressLooper*BucketSize + i]->getItem();
                    return true;
                }
            }
        }
        
    }
    
    printf("Entry Not Found!\n");
    return false;
    
}

/***********************************************
 printHashIndented: takes in void function, uses function
 to print every element of the hash with indented synonyms
 **********************************************/

template <class T>
void hashTable<T>::printHashIndented(void printEntry(T entry)) {
    for (int i = 0; i < numberOfBuckets*BucketSize; i++) {
        //cout << "display item: \n";
        if ( i%BucketSize == 0) {
            cout << "Bucket: " << i/BucketSize << "  ";
            if (table[i] == NULL) {
                cout << "EMPTY!"<<endl;
            }
        }
        if(table[i] != NULL){
            if (i % BucketSize) {cout << "\t\t\t\t";}
            printEntry(table[i]->getItem());
        }
        if (i % BucketSize == BucketSize-1) {cout <<endl;}
    }
}

/***********************************************
 printHash: takes in void function, uses function
 to print every element of the hash
 **********************************************/

template <class T>
void hashTable<T>::printHash(void printEntry(T entry)) {
    for (int i = 0; i < numberOfBuckets*BucketSize; i++) {
        if(table[i] != NULL){
            printEntry(table[i]->getItem());
        }
    }
}

/***********************************************
 displayStats: void function, no input parameters.
 displays statistics of the hash table
 **********************************************/

template <class T>
void hashTable<T>::displayStats() {
    cout.precision(3.1);
    cout << "\nLoad Factor                : " <<(double)bucketsTaken/(double)numberOfBuckets *100<< "%" <<endl;
    cout << "Number of buckets          : " << numberOfBuckets << endl;
    cout << "Size of buckets            : " << BucketSize <<endl;
    cout << "Number of taken buckets    : " << bucketsTaken <<  endl;
    cout << "Number of empty buckets    : " << numberOfBuckets - bucketsTaken << " Out of " << numberOfBuckets<<endl;
    cout << "Number of entries          : " << count << " out of " << numberOfBuckets*BucketSize<<endl;
    cout << "Number of collisions       : " << collisions << endl;
    cout << "Number of failed inserts   : " << failedInserts << endl;
    cout << "\n\n";
    //cout <<
}

/***********************************************
 ~hashTable: destructor
 **********************************************/

template <class T>
hashTable<T>::~hashTable() {
    for (int i = 0; i < numberOfBuckets*BucketSize; i++) {
        if(table[i] != NULL){
            delete table[i];
        }
    }
    delete table;
}

#endif /* defined(__HW5__hashTable__) */
