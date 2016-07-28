//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#ifndef Account_Kai_h
#define Account_Kai_h

class Account // base class
{
private:
    double cashBalance;
public:
    Account();
    double getCashBalance();
    void setCashBalance(double);
};


#endif /* defined(__FInalProject__Account_Kai__) */
