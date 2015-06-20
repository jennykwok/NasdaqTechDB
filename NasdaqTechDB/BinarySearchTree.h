// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Reuse the code from HW4

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <stdio.h>
#include <iostream>

using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
    
protected:
    //Root of tree
    //BinaryNode<ItemType>* rootPtr;
    int count;
    
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
    
    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
    
    
    void _printRange(void visit(ItemType &),BinaryNode<ItemType>* nodePtr,ItemType & min,ItemType & max);
    
    BinaryNode<ItemType> *findLeftOrRight(BinaryNode<ItemType>* treePtr,bool getLeft);
    
public:
    // insert a node at the correct location
    bool insert(const ItemType & newEntry);
    // remove a node if found
    bool remove(const ItemType & anEntry);
    // find a target node
    bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    
    void printRange(void visit(ItemType &),ItemType & min, ItemType & max){_printRange(visit, this->rootPtr, min, max);};
    
    void printMinOrMax(void visit(ItemType &),bool getMin);
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}


/***********************************************
 getEntry: take in an object to be found and and address
 of an object, returns the result of the search. Call the
 find node function, if target node is found save the found node
 and return true else return false.
 **********************************************/


template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    
    
    BinaryNode<ItemType> *foundNode = findNode(this->rootPtr, anEntry);
    
    if(foundNode != NULL){
        returnedItem = foundNode->getItem();
        return true;
    }else{
        return false;
    }
    
    //return false;
    
}

/***********************************************
 printMinOrMax: takes in a void function used to print the
 node, and a bool getMin. If getMin is true then function finds the
 smallest element in the tree and displays, if false it finds the largest.
 **********************************************/

template<class ItemType>
void BinarySearchTree<ItemType>::printMinOrMax(void visit(ItemType &),bool getMin)
{
    BinaryNode<ItemType> *minOrMax = findLeftOrRight(this->rootPtr,getMin);
    ItemType minItem = minOrMax->getItem();
    visit(minItem);
    
}

/***********************************************
 _printRange: takes in a void function to print the nodes
 and two item used to determine the range. traverses the tree
 and prints all nodes within the range of the two items
 passed in.
 **********************************************/

template<class ItemType>
void BinarySearchTree<ItemType>::_printRange(void visit(ItemType &),BinaryNode<ItemType>* nodePtr,ItemType & min, ItemType & max)
{
    
    if (nodePtr != 0)
    {
        _printRange(visit, nodePtr->getLeftPtr(),min,max);
        ItemType item = nodePtr->getItem();
        if (item > max) {
            return;
        }else if(item >= min){
            visit(item);
        }
        _printRange(visit, nodePtr->getRightPtr(),min,max);
        
    }
    
    
}



//////////////////////////// private functions ////////////////////////////////////////////


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    this->count++;
    
    if (nodePtr != NULL) {
        BinaryNode<ItemType> *parent = nodePtr;
        //printf("parent data is %d\n",parent->getItem());
        
        BinaryNode<ItemType> *curr;
        while (nodePtr != NULL) {
            curr = nodePtr;
            if (newNodePtr->getItem() > nodePtr->getItem()) {
                nodePtr = nodePtr->getRightPtr();
                if (nodePtr == NULL) {
                    curr->setRightPtr(newNodePtr);
                }
            }else{
                nodePtr = nodePtr->getLeftPtr();
                if (nodePtr == NULL) {
                    curr->setLeftPtr(newNodePtr);
                }
            }
        }
        return parent;
    }else{
        nodePtr = newNodePtr;
        return nodePtr;
    }
    
    //return parent;
}



template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (nodePtr->getItem() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}


/***********************************************
 findNode: takes in a pointer to the root of of the tree
 and item to be found. Traveres the tree and returns the item
 if found, if item is not found returns NULL
 **********************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const
{
    
    while (nodePtr != NULL) {
        //if (true) {
        if ((ItemType)target == nodePtr->getItem()) {
            return nodePtr;
        }else if((ItemType)target > nodePtr->getItem()){
            nodePtr = nodePtr->getRightPtr();
        }else{
            nodePtr = nodePtr->getLeftPtr();
        }
    }
    return NULL;
}


/***********************************************
 findLeftOrRight: takes in a pointer to the root of the tree
 and bool getLeft, if getLeft is tree function finds the left
 most node in the tree and returns it, else if getLeft is false
 then function finds the right most node in the tree and returns it.
 **********************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLeftOrRight(BinaryNode<ItemType>* nodePtr, bool getLeft)

{
    if(getLeft){
        BinaryNode<ItemType>* leftMostNode = nodePtr;
        if (nodePtr->getLeftPtr() != 0)
        {
            leftMostNode = findLeftOrRight(nodePtr->getLeftPtr(),getLeft);
        }
        return leftMostNode;
    }else{
        BinaryNode<ItemType>* rightMostNode = nodePtr;
        if (nodePtr->getRightPtr() != 0)
        {
            rightMostNode = findLeftOrRight(nodePtr->getRightPtr(),getLeft);
        }
        return rightMostNode;
        
    }
    
}


#endif
