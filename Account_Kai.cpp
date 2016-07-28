//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#include "Account_Kai.h"

#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;


#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

std::vector<std::string> split(std::string str,std::string pattern) // a function to split the string
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern; //expand the string
    int size = (int) str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i = pos+pattern.size() - 1;
        }
    }
    return result;
}

Account::Account() // constructor
{
    string line;
    ifstream myfile ("cashBalance.txt"); // check if a new user
    if (myfile.is_open()) // old user
    {

        getline(myfile, line);
        vector<string> result = split(line, "$");
        cashBalance = stod(result[1], NULL);
        myfile.close();
    }
    else // a new user
    {
        //creat a new file
        ofstream in;
        in.open("cashBalance.txt", ios::trunc);
        in << "$10000" << endl;

        cashBalance = 10000;
        
    }
}

void Account::setCashBalance(double money)
{
    cashBalance = money;
}

double Account::getCashBalance()
{
    return cashBalance;
}

