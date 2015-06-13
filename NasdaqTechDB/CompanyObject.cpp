//
//  CompanyObject.cpp
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/8/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#include "CompanyObject.h"

CompanyObject::CompanyObject(){
    this->keyNumber = 0;
    this->key[0] = "";
    this->key[1] = "";
    this->key[2] = "";
    this->country = "";
    this->CEO = "";
    this->subsector = "";
}

CompanyObject::CompanyObject(int keyNumber, string tickerSymbol, string companyName, string IPO_date, string country, string CEO, string subsector){
    this->keyNumber = keyNumber;
    this->key[0] = tickerSymbol;
    this->key[1] = IPO_date;
    this->key[2] = companyName;
    this->country = country;
    this->CEO = CEO;
    this->subsector = subsector;
}

bool CompanyObject::operator>(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) > 0) {
        return true;
    }else{
        return false;
    }
}

bool CompanyObject::operator<(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) < 0) {
        return true;
    }else{
        return false;
    }
    
}

bool CompanyObject::operator==(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) == 0) {
        return true;
    }else{
        return false;
    }
    
}

bool CompanyObject::operator>=(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) > 0 || key[keyNumber].compare(compare.key[keyNumber]) == 0) {
        return true;
    }else{
        return false;
    }
    
}

bool CompanyObject::operator<=(const CompanyObject &compare){
    if (key[keyNumber].compare(compare.key[keyNumber]) < 0 || key[keyNumber].compare(compare.key[keyNumber]) == 0) {
        return true;
    }else{
        return false;
    }
}

void CompanyObject::displayCompany(){
    cout << this->key[0] << " " << this->key[2] << " (" << this->subsector << ") " << endl;
    cout << this->CEO << " " <<this->key[1] << " " << this->country << "\n" << endl;
    
}
