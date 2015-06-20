//
//  BST_Menu.h
//  NasdaqTechDB
//
//  Author: Jenny
//
//   Description:
//      This is the header file where
//      the menu, search and display functions are added from
//      the abstract BST ADT.

#ifndef __NasdaqTechDB__BST_Menu__
#define __NasdaqTechDB__BST_Menu__

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "CompanyObject.h"
#include "BinarySearchTree.h"

BinarySearchTree<CompanyObject> *buildCompanyTree(string fileName, int keyNumber);
void displayCompany(CompanyObject &company);
void displayIndentedTree(CompanyObject &company, int level);
void BST_Menu(int keyNumber,BinarySearchTree<CompanyObject>* tree2Ptr);
void BSTSearchOption(int keyNumber, BinarySearchTree<CompanyObject>* tree2Ptr);
void displayBSTMenu();

#endif /* defined(__NasdaqTechDB__BST_Menu__) */
