//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#include "Bank_Kai.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;

BankAccount::BankAccount(double money) // constructor
: Account()
{
    setCashBalance(money);
}

void BankAccount::viewBalance()
{
    cout << "You have $" << getCashBalance() << " in your bank account" << endl;
}

double BankAccount::deposit() // make a deposit
{
    cout << "Please select the amount you wish to deposit: $";
    double deposit;
    cin >> deposit;
    setCashBalance(getCashBalance()+deposit);
    
    // write the transaction history
    ifstream check("bank_transaction_history.txt");// check if the history file exist
    if (!check.is_open()) {
        //creat history file
        ofstream newhistoryFile;
        newhistoryFile.open("bank_transaction_history.txt", ios::trunc);
        newhistoryFile << setw(10) << "Event" << setw(10) << "Amount" << setw(15) << "Time" << endl;
        newhistoryFile.close();
    }
    //write
    ofstream historyFile;
    historyFile.open("bank_transaction_history.txt", ios::app);
    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    historyFile << setw(10) << "Deposit" << setw(10) << deposit << setw(30) << asctime(timeinfo) << endl;
    historyFile.close();
    
    return getCashBalance();
}

double BankAccount::withdraw() // make a withdraw
{
    cout << "Please select the amount you wish to withdraw: $";
    double withdraw;
    cin >> withdraw;
    double cash = getCashBalance();
    if (cash < withdraw) { // check the current money
        cout << "Transaction Failed: You do not have that much money." << endl;
        return cash;
    }
    setCashBalance(getCashBalance() - withdraw);
    
    // write the transaction history
    ifstream check("bank_transaction_history.txt");// check if the history file exist
    if (!check.is_open()) {
        //creat history file
        ofstream newhistoryFile;
        newhistoryFile.open("bank_transaction_history.txt", ios::trunc);
        newhistoryFile << setw(10) << "Event" << setw(10) << "Amount" << setw(15) << "Time" << endl;
        newhistoryFile.close();
    }
    //write
    ofstream historyFile;
    historyFile.open("bank_transaction_history.txt", ios::app);
    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    historyFile << setw(10) << "Withdraw" << setw(10) << withdraw << setw(30) << asctime(timeinfo) << endl;
    historyFile.close();
    
    return getCashBalance();
}

void BankAccount::printHistory()
{
    ifstream check("bank_transaction_history.txt");// check if the history file exist
    if (!check.is_open()) {
        cout << "You don't have any transactions yet" << endl;
        return;
    }
    ifstream historyFile("bank_transaction_history.txt");
    string historyLine;
    cout << "\t\t TRANSACTION HISTORY" << endl;
    cout << endl;
    while(getline(historyFile, historyLine))
    {
        cout << historyLine << endl;
    }
}
