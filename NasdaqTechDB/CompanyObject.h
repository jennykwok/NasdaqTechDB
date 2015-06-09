//
//  CompanyObject.h
//  NasdaqTechDB
//
//  Created by Jenny Kwok on 6/8/15.
//  Copyright (c) 2015 Jenny Kwok. All rights reserved.
//

#ifndef ____CompanyObject__
#define ____CompanyObject__

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CompanyObject {
    
private:
    int keyNumber;
    string key[2];
    string companyName;
    string country;
    string CEO;
    string subsector;
    
public:
    bool operator>(const CompanyObject &compare);
    bool operator<(const CompanyObject &compare);
    bool operator==(const CompanyObject &compare);
    bool operator>=(const CompanyObject &compare);
    bool operator<=(const CompanyObject &compare);
    
    CompanyObject();
    CompanyObject(int keyNumber, string tickerSymbol, string companyName, string IPO_date, string country, string CEO, string subsector);
    ~CompanyObject(){};
    
    string getTickerSymbol(){return key[0];}
    string getCompanyName(){return companyName;}
    string getIPO_date(){return key[1];}
    string getCountry(){return country;}
    string getCEO(){return CEO;}
    string getSubsector(){return subsector;}
    
    void setCompanyName(string companyName){this->companyName = companyName;}
    //void setIPO_date(string IPO_date){this->IPO_date = IPO_date;}
    void setCountry(string Country){this->country = Country;}
    void setCEO(string CEO){this->CEO = CEO;}
    void setSubsector(string subsector){this->subsector = subsector;}
    
    void displayCompany();
    
};

#endif /* defined(__NasdaqTechDB__CompanyObject__) */
