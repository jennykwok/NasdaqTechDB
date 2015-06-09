//
//  BST_Menu.cpp
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/9/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#include "BST_Menu.h"

void displayCompany(CompanyObject &company){
    company.displayCompany();
}

void displayIndentedTree(CompanyObject &company, int level){
    cout << setw(13*level) << "L." << level << " "  << company.getTickerSymbol() << endl;
}




BinarySearchTree<CompanyObject> *buildCompanyTree(string fileName, int keyNumber){
    BinarySearchTree<CompanyObject> *treePtr = new BinarySearchTree<CompanyObject>();
    ifstream inputFile(fileName);
    
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
        
        CompanyObject newCompany = CompanyObject(keyNumber,tickerSymbol,companyName,IPO_date,country,CEO,subsector);
        CompanyObject temp;
        if (!treePtr->getEntry(newCompany, temp)) {
            treePtr->insert(newCompany);
        }else{
            cout << "Failed to insert, company already exist in database!" <<endl;
        }
        
    }
    
    
    inputFile.close();
    return treePtr;
}


void BST_Menu(int keyNumber, BinarySearchTree<CompanyObject>* tree2Ptr){
    
    cout << "\n***Entering Binary Search Tree ("<< ((keyNumber == 0) ? "ticker symbol)***\n":"IPO date)***\n") <<endl;
    
    
    char option;
    char line[128];
    bool inMenu = true;
    
    CompanyObject temp;
    while (inMenu) {
        
        cout << "Please enter an option (H for help): ";
        cin.getline(line, 127);
        option = line[0];
        
        switch (option) {
            case 'B':
                cout << "Displaying Breadth-First\n" << endl;
                tree2Ptr->breadth(displayCompany);
                cout << "\n\n" <<endl;
                break;
                
            case 'D':
                cout << "Displaying Depth-First Traversal (Recursive)\n" << endl;
                cout <<"In Order Traversal \n"<<endl;
                tree2Ptr->inOrder(displayCompany);
                cout <<"\n\n\nPost Order Traversal \n"<<endl;
                tree2Ptr->postOrder(displayCompany);
                cout <<"\n\n\nPre Order Traversal \n"<<endl;
                tree2Ptr->preOrder(displayCompany);
                cout << "\n\n" <<endl;
                break;
                
            case 'I':
                cout << "Displaying Depth-First Traversal (Iterative)\n" << endl;
                cout <<"In Order Traversal \n"<<endl;
                tree2Ptr->inOrderIterative(displayCompany);
                cout <<"\n\n\nPost Order Traversal \n"<<endl;
                tree2Ptr->postOrderIterative(displayCompany);
                cout <<"\n\n\nPre Order Traversal \n"<<endl;
                tree2Ptr->preOrderIterative(displayCompany);
                cout << "\n\n" <<endl;
                
                break;
                
            case 'T':
                cout << "Displaying Indented Tree\n" << endl;
                tree2Ptr->indentedTree(displayIndentedTree);
                break;
                
            case 'S':{
                
                cout << "Enter company " << ((keyNumber == 0) ? "ticker symbol: ":"IPO date: ");
                char companyKey[128];
                cin.getline(companyKey, 127);
                if (tree2Ptr->getEntry(CompanyObject(keyNumber,companyKey,"",companyKey,"","",""), temp)) {
                    displayCompany(temp);
                    cout << "\n\n" << endl;
                }else{
                    cout << "Cound Not Find company\n\n" <<endl;
                }
                break;
            }
            case 'R':{
                
                char companyKey[128];
                cout << "Please enter first company " << ((keyNumber == 0) ? "ticker symbol: ":"IPO date: ");
                cin.getline(companyKey, 127);
                CompanyObject company1 = CompanyObject(keyNumber,companyKey,"",companyKey,"","","");
                cout << "Please enter last company " << ((keyNumber == 0) ? "ticker symbol: ":"IPO date: ");
                cin.getline(companyKey, 127);
                CompanyObject company2 = CompanyObject(keyNumber,companyKey,"",companyKey,"","","");
                tree2Ptr->printRange(displayCompany, company1, company2);
                cout << "\n\n" <<endl;
                break;
            }
            case 'A':
                cout << "Developer Name" <<endl;
                break;
                
            case 'H':
                cout << "B – Tree Breadth-First Traversal: Print by level"<<endl;
                cout << "D – Depth-First Traversals: inorder, preorder, postorder"<<endl;
                cout << "I – Iterative Depth-First Traversals: inorder, preorder, postorder"<<endl;
                cout << "T – Print tree as an indented list "<<endl;
                cout << "S – Search by a unique key"<<endl;
                cout << "R – Print the items within a given range in the tree"<<endl;
                cout << "H – Help – to show the menu"<<endl;
                cout << "Q – Quit\n\n"<<endl;
                break;
                
            case 'Q':
                cout << "BST Menu exited!\n\n" <<endl;
                inMenu = false;
                break;
                
            default:
                break;
        }
    }
    
    
}