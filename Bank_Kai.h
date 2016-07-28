//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#ifndef Bank_Kai_h
#define Bank_Kai_h

#include "Account_Kai.h"
#include "Stock_Kai.h"

class BankAccount : public Account
{
public:
    BankAccount(double);
    void viewBalance();
    double deposit();
    double withdraw();
    void printHistory();
};

#endif /* defined(__FInalProject__Bank_Kai__) */
