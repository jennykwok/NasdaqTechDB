//
//  CompanyObject.cpp
//  NasdaqTechDB
//
//  Athour: Tony
//
// implementation file for the company object

#include "CompanyObject.h"

/***********************************************
Default Constructor CompanyObject: initalizes
 everything to empty string and zeros.
 **********************************************/
CompanyObject::CompanyObject(){
    this->keyNumber = 0;
    this->key[0] = "";
    this->key[1] = "";
    this->key[2] = "";
    this->country = "";
    this->CEO = "";
    this->subsector = "";
}

/***********************************************
 Constructor CompanyObject: initalizes
 everything to the parameters taken in.
 **********************************************/
CompanyObject::CompanyObject(int keyNumber, string tickerSymbol, string companyName, string IPO_date, string country, string CEO, string subsector){
    this->keyNumber = keyNumber;
    this->key[0] = tickerSymbol;
    this->key[1] = IPO_date;
    this->key[2] = companyName;
    this->country = country;
    this->CEO = CEO;
    this->subsector = subsector;
}

/***********************************************
 Operator > overload: does a string comparison
 between the key set by the index of the key array
 and returns true if greater.
 **********************************************/
bool CompanyObject::operator>(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) > 0) {
        return true;
    }else{
        return false;
    }
}

/***********************************************
 Operator < overload: does a string comparison
 between the key set by the index of the key array
 and returns true if less than.
 **********************************************/
bool CompanyObject::operator<(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) < 0) {
        return true;
    }else{
        return false;
    }
    
}

/***********************************************
 Operator == overload: does a string comparison
 between the key set by the index of the key array
 and returns true if equal.
 **********************************************/
bool CompanyObject::operator==(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) == 0) {
        return true;
    }else{
        return false;
    }
    
}

/***********************************************
 Operator >= overload: does a string comparison
 between the key set by the index of the key array
 and returns true if greater than or equal.
 **********************************************/
bool CompanyObject::operator>=(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) > 0 || key[keyNumber].compare(compare.key[keyNumber]) == 0) {
        return true;
    }else{
        return false;
    }
    
}

/***********************************************
 Operator <= overload: does a string comparison
 between the key set by the index of the key array
 and returns true if less than or equal.
 **********************************************/
bool CompanyObject::operator<=(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) < 0 || key[keyNumber].compare(compare.key[keyNumber]) == 0) {
        return true;
    }else{
        return false;
    }
}

/***********************************************
displayCompany: Displays the compant object
 to the console in an neatly formatted way for 
 the end user to browse through.
 **********************************************/
void CompanyObject::displayCompany(){
    cout << "\n\t| " << this->key[0] << " " << this->key[2] << " (" << this->subsector << ") " << endl;
    cout << "\t| " << this->CEO << " " <<this->key[1] << " " << this->country << "\n" << endl;
    
}
