//
//  BST_Menu.h
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/9/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

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
void BST_Menu(int keyNumber,BinarySearchTree<CompanyObject>* tree2Ptr);
void displayBSTMenu();

#endif /* defined(__NasdaqTechDB__BST_Menu__) */
