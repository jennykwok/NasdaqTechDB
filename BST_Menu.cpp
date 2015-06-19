//
//  BST_Menu.cpp
//  NasdaqTechDB
//
//   Description:
//      This is the implementation file for BST_Menu.h where
//      the menu, input to BSt, search and display functions are implemented from
//      the abstract BST ADT.

#include "BST_Menu.h"

/***********************************************
displayCompany: Calls the display company function
 of the company class taken in as an argument
 to print the company data
 out to console usual fulfilling the user request
 for such data
 **********************************************/
void displayCompany(CompanyObject &company){
    company.displayCompany();
}

/***********************************************
displayIndentedTree: Takes in a company object
 and the level number by int and formats the 
 output by indenting in a multiple of 13 the
 amount taken in from level. It outputs the 
 company information with indentation.
 **********************************************/
void displayIndentedTree(CompanyObject &company, int level){
    cout << setw(13*level) << "L." << level << " "  << company.getTickerSymbol() << endl;
}

/***********************************************
buildCompanyTree: takes string for filename, reads data from file
 and produces a BST with entries populated from file. The function
 returns a pointer to the BST.
 **********************************************/
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


/***********************************************
 BST_Menu: Take in the company BST pointer
 and uses the switch to create dev menu for the end user to interact
 and to use to get various information offered
 by the NASDAQ program
 **********************************************/
void BST_Menu(int keyNumber, BinarySearchTree<CompanyObject>* tree2Ptr){
    
    cout << "\n\n----------- Entering Binary Search Tree ("<< ((keyNumber == 0) ? "ticker symbol) -----------":"IPO date) ----------------") <<endl;
    displayBSTMenu(); //prints the full menu
    
    char option;
    char line[128];
    bool inMenu = true; //bool to exit out of menu loop
    
    CompanyObject temp;
    while (inMenu) {
        
        cout << "Enter Option: ";
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
                
                BSTSearchOption(keyNumber, tree2Ptr);
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
                
            case 'M':
                displayBSTMenu();
                break;
                
            case 'Q':
                cout << "BST Menu exited!" <<endl;
                inMenu = false;
                break;
                
            default:
                break;
        }
    }
}

/***********************************************
displayBSTMenu: outputs the menu to user
 **********************************************/
void displayBSTMenu()
{
    cout << "B – Tree Breadth-First Traversal: Print by level"<<endl;
    cout << "D – Depth-First Traversals: inorder, preorder, postorder"<<endl;
    cout << "I – Iterative Depth-First Traversals: inorder, preorder, postorder"<<endl;
    cout << "T – Print tree as an indented list "<<endl;
    cout << "S – Search by a unique key"<<endl;
    cout << "R – Print the items within a given range in the tree"<<endl;
    cout << "H – Help – to show the menu"<<endl;
    cout << "Q – Quit\n"<<endl;

}

/***********************************************
BSTSearchOption: takes a keyNumber that will
 specify the key to use(ticker or IPO) and a 
 pointer to the BST. If entry found, it outputs the
 information to user. If not, not found is outputed.
 **********************************************/
void BSTSearchOption(int keyNumber, BinarySearchTree<CompanyObject>* tree2Ptr){
    CompanyObject temp;
    char companyKey[128];
    
    while (1) {
        cout << "Enter company " << ((keyNumber == 0) ? "ticker symbol (QUIT to stop searching): ":"IPO date (QUIT to stop searching): ");
        cin.getline(companyKey, 127);
        if (strcmp(companyKey, "QUIT") == 0) {break;}
        if (tree2Ptr->getEntry(CompanyObject(keyNumber,companyKey,"",companyKey,"","",""), temp)) {
            displayCompany(temp);
            cout << "\n\n" << endl;
        }else{
            cout << "Cound Not Find company\n\n" <<endl;
        }

    }
    
    cout << "" <<endl;
}