//
//  hashEntry.h
//
//  Reuse the code from HW5
//
//  Hash Entry ADT Header file

#ifndef HW5_hashEntry_h
#define HW5_hashEntry_h

#include <stdio.h>

template <class ItemType>
class hashEntry {
private:
    int key;
    ItemType item;
    
public:
    
    //Constructors
    hashEntry(){key = -1; item = NULL;}     // default constructors
    hashEntry(int hashFunc(ItemType newEntry,int numberOfBuckets), const ItemType & newEntry, int numberOfBuckets);
    
    //Destructor
    ~hashEntry();
    
    //Getters
    int getKey(){return  key;}
    ItemType getItem(){return item;}
    
    //Setters
    void UpdateKey(int hashFunc(ItemType &newEntry,int numberOfBuckets),int numberOfBuckets){
        key = hashFunc(this->item,numberOfBuckets);
    };
    void setItem(ItemType item){this->item = item;}
    
};


template <class ItemType>
hashEntry<ItemType>::hashEntry(int hashFunc(ItemType newEntry,int numberOfBuckets), const ItemType & newEntry, int numberOfBuckets) {
    this->item = newEntry;
    this->key = hashFunc(item,numberOfBuckets);
}

template <class ItemType>
hashEntry<ItemType>::~hashEntry(){
    
}

#endif
