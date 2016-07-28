//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#ifndef Stock_Kai_h
#define Stock_Kai_h

#include "Account_Kai.h"
#include "LinkedList_Kai.h"
#include <vector>
#include <string>
using namespace std;

class StockAccount : public Account
{
public:
    StockAccount(double);
    ~StockAccount();
    void showPrice();
    double getPrice(string);
    void displayPortfolio();
    double buyShare();
    double sellShare();
    void viewHistory();
    void viewGraph();

private:
    vector <vector<string>> stockPrices;
    LinkedList portfolioList;

};


#endif /* defined(__FInalProject__Stock_Kai__) */
