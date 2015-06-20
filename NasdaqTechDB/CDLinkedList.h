//
//  CDLinkedList.h
//  Reuse the code from HW3
//
// Circularly Doubly Linked List ADT

#ifndef HW3_CDLinkedList_h
#define HW3_CDLinkedList_h

#include <stdio.h>
#include <iostream>
using namespace std;

template <typename T>
struct ListNode{
    T value;
    ListNode *next;
    ListNode *prev;
};

template <class T>
class CDLinkedList {
    
private:
    
    ListNode<T> *head;
    int count;
    
public:
    
    // Constructor
    CDLinkedList();
    
    // Destructor
    ~CDLinkedList();
    
    int getCount();
    void insertBack(T item);
    void insertFront(T item);
    bool popFront(T *item);
    void printList();
    ListNode<T> *getHead();
    
    
};

/***********************************************
 Constructor: Creates sentinel node and set both forward and backward
 pointer to the sentinal. Make the sentinal the head of the list and
 intiallize count to 0
 **********************************************/

template <class T>
CDLinkedList<T> ::CDLinkedList() {
    head = new ListNode<T>;
    head->next = head;
    head->prev = head;
    head->value = NULL;
    count = 0;
}

/***********************************************
 Destructor: Start at the head, remove links connecting the head and tail
 of the list. Then we iterate through the list deleting each node untill we
 reach the end.
 **********************************************/
template <class T>
CDLinkedList<T> ::~CDLinkedList() {
    ListNode<T> *curr = head;
    while (curr) {
        ListNode<T> *temp = curr->next;
        if (curr->prev) {
            curr->prev->next = NULL;
        }
        delete curr;
        curr = temp;
    }
}

/***********************************************
 Get Count: simply returns the count.
 **********************************************/

template <class T>
int CDLinkedList<T>::getCount() {
    return count;
}

/***********************************************
 insertBack: create a new node, set the value to
 be the value passed in, and insert at the back
 updating the pointers.
 **********************************************/

template <class T>
void CDLinkedList<T>::insertBack(T item) {
    
    // Create new node and set value
    ListNode<T> *newNode = new ListNode<T>;
    newNode->value = item;
    
    // Update pointers
    newNode->next = head;
    newNode->prev = head->prev;
    head->prev->next = newNode;
    head->prev = newNode;
    
    // Increment counter
    count++;
}

/***********************************************
 insertFront: create a new node, set the value to
 be the value passed in, and insert at the front
 updating the pointers.
 **********************************************/

template <class T>
void CDLinkedList<T>::insertFront(T item) {
    
    // Create new node and set value
    ListNode<T> *newNode = new ListNode<T>;
    newNode->value = item;
    
    // Update pointers
    newNode->prev = head;
    newNode->next = head->next;
    
    head->next->prev = newNode;
    head->next = newNode;
    
    // Increment counter
    count++;
}

/***********************************************
 popFront: pops off first element of the linked
 list and stores it into the address passed in.
 **********************************************/
template <class T>
bool CDLinkedList<T>::popFront(T *item) {
    
    if (count > 0) {
        *item = head->next->value;
        ListNode<T> *temp = head->next;
        head->next->next->prev = head;
        head->next = head->next->next;
        delete temp;
        count--;
        return true;
    }else{
        return false;
    }
}

/***********************************************
 printList: start at the node after the head and print the value
 of each node untill we return to the head (Circularly linked list).
 **********************************************/

template <class T>
void CDLinkedList<T>::printList() {
    
    ListNode<T> *curr = head->next;
    while (curr != head) {
        cout << curr->value;
        curr = curr->next;
    }
    std:cout<<endl;
    
}

/***********************************************
 getHead: simply returns the head of the list aka the sentinel node.
 **********************************************/

template <class T>
ListNode<T> *CDLinkedList<T>::getHead() {
    return head;
}

#endif
