// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Reuse the code from HW4

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "CDLinkedList.h"
#include <stdio.h>

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;		// ptr to root node
    int count;							// number of nodes in tree
    
public:
    // "admin" functions
    BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree<ItemType> & tree){ }
    virtual ~BinaryTree() {destroyTree(rootPtr);}
    BinaryTree & operator = (const BinaryTree & sourceTree);
    
    // common functions for all binary trees
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
    void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
    void preOrderIterative(void visit(ItemType &)) const {_preorderIterative(visit, rootPtr);}
    void inOrderIterative(void visit(ItemType &)) const  {_inorderIterative(visit, rootPtr);}
    void postOrderIterative(void visit(ItemType &)) const{_postorderIterative(visit, rootPtr);}
    void indentedTree(void visit(ItemType &,int level)) const{_indentedTree(visit, rootPtr,1);}
    void breadth(void visit(ItemType &)) const{_breadth(visit, rootPtr);}
    
    // abstract functions to be implemented by derived class
    virtual bool insert(const ItemType & newData) = 0;
    virtual bool remove(const ItemType & data) = 0;
    virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
    
private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);
    
    // copy from the tree rooted at nodePtr and returns a pointer to the copy
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);
    
    // internal traverse
    void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    
    void _preorderIterative(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _inorderIterative(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _postorderIterative(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _indentedTree(void visit(ItemType &, int level), BinaryNode<ItemType>* nodePtr,int level) const;
    void _breadth(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    
    
};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType>* newNodePtr = 0;
    
    
    return newNodePtr;
}

/***********************************************
 destroyTree: recursively function starts on that
 traverses the tree inorder deleting the nodes
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    
    if (nodePtr != 0) {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
}

/***********************************************
 _preorder: recursive function, takes in a void function used to print
 the node and a node pointer. Traverses the tree in preorder calling
 the void function passed in on each node.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

/***********************************************
 _inorder: recursive function, takes in a void function used to print
 the node and a node pointer. Traverses the tree inorder calling
 the void function passed in on each node.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    
    if (nodePtr != 0)
    {
        _inorder(visit, nodePtr->getLeftPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
        
        
    }
}

/***********************************************
 _postorder: recursive function, takes in a void function used to print
 the node and a node pointer. Traverses the tree in post calling
 the void function passed in on each node.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
        
    }
}

/***********************************************
 _preorderIterative: iterative function, takes in a void function used to print
 the node and a node pointer. Traverses the tree in preorder calling
 the void function passed in on each node.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_preorderIterative(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    
    if (nodePtr != 0)
    {
        CDLinkedList<BinaryNode<ItemType>*> *stack = new CDLinkedList<BinaryNode<ItemType>*>;
        stack->insertFront(nodePtr);
        while(stack->getCount()){
            BinaryNode<ItemType> *curr;
            stack->popFront(&curr);
            if (curr->getRightPtr() != NULL) {
                stack->insertFront(curr->getRightPtr());
            }
            if (curr->getLeftPtr() != NULL) {
                stack->insertFront(curr->getLeftPtr());
            }
            
            ItemType item = curr->getItem();
            visit(item);
            
        }
    }
}

/***********************************************
 _inorderIterative: iterative function, takes in a void function used to print
 the node and a node pointer. Traverses the tree inorder calling
 the void function passed in on each node.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_inorderIterative(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    
    if (nodePtr != 0)
    {
        CDLinkedList<BinaryNode<ItemType>*> *stack = new CDLinkedList<BinaryNode<ItemType>*>;
        BinaryNode<ItemType> *curr = nodePtr;
        
        while(stack->getCount() || curr != NULL){
            
            if (curr != NULL) {
                stack->insertFront(curr);
                curr = curr->getLeftPtr();
            }else{
                stack->popFront(&curr);
                ItemType item = curr->getItem();
                visit(item);
                curr = curr->getRightPtr();
            }
            
        }
        
    }
}

/***********************************************
 _postorderIterative: iterative function, takes in a void function used to print
 the node and a node pointer. Traverses the tree in postorder calling
 the void function passed in on each node.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_postorderIterative(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        CDLinkedList<BinaryNode<ItemType>*> *stack = new CDLinkedList<BinaryNode<ItemType>*>;
        BinaryNode<ItemType> *curr = nodePtr;
        BinaryNode<ItemType> *lastNodeVisited = NULL;
        
        while(stack->getCount() || curr != NULL){
            
            if (curr != NULL) {
                stack->insertFront(curr);
                curr = curr->getLeftPtr();
            }else{
                BinaryNode<ItemType> *peek;
                stack->popFront(&peek);
                stack->insertFront(peek);
                if (peek->getRightPtr() != NULL && peek->getRightPtr() != lastNodeVisited) {
                    curr = peek->getRightPtr();
                }else{
                    ItemType item = peek->getItem();
                    visit(item);
                    stack->popFront(&lastNodeVisited);
                    
                }
                
            }
            
        }
    }
}

/***********************************************
 _indentedTree: recursive function, takes in a void function used to print
 the node, a node pointer, and an int level. Traverses the tree Depth first
 right-root-left printing each node line by line.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_indentedTree(void visit(ItemType &, int level), BinaryNode<ItemType>* nodePtr,int level) const
{
    
    if (nodePtr != 0)
    {
        level++;
        _indentedTree(visit, nodePtr->getRightPtr(),level);
        level--;
        ItemType item = nodePtr->getItem();
        visit(item,level);
        level++;
        _indentedTree(visit, nodePtr->getLeftPtr(),level);
        level--;
        
        
    }
}

/***********************************************
 _breadth: takes in a void function used to print
 the node and node pointer to the root of the tree.
 Inserts the root into a queue and whill the queue is
 not empty dequeue a node and process it. IE add its
 children to the queue then call the void function to
 print it.
 **********************************************/

template<class ItemType>
void BinaryTree<ItemType>::_breadth(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        
        CDLinkedList<BinaryNode<ItemType>*> *queue = new CDLinkedList<BinaryNode<ItemType>*>;
        queue->insertBack(nodePtr);
        while (queue->getCount()) {
            BinaryNode<ItemType> *curr;
            queue->popFront(&curr);
            if (curr->getLeftPtr() != NULL) {
                queue->insertBack(curr->getLeftPtr());
            }
            if (curr->getRightPtr() != NULL) {
                queue->insertBack(curr->getRightPtr());
            }
            ItemType item = curr->getItem();
            visit(item);
            
        }
    }
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
    
}  


#endif