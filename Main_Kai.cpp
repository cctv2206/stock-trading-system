//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//


#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#include "Account_Kai.h"
#include "Stock_Kai.h"
#include "Bank_Kai.h"

int main()
{
    Account user = Account();
    StockAccount stockAccount = StockAccount(user.getCashBalance());
    BankAccount bankAccount = BankAccount(user.getCashBalance());

    cout << "Welcome to the Account Management System." << endl;
    int todo = 0;
    int choice = 0;
    while (todo != 3) {
        switch (todo) {
            case 0: //show the menu
                cout << endl;
                cout << "Please select an account to access:" << endl;
                cout <<"1. Stock Portfolio Account" << endl;
                cout <<"2. Bank Account" << endl;
                cout <<"3. Exit" << endl;
                cout << "Option: ";
                cin >> todo;
                break;
            case 1: // Stock Portfolio Account
            {
                choice = 0;
                while (choice != 7) {
                    switch (choice) {
                        case 0: // show the menu 1
                            cout << endl;
                            cout << "Please select an option:" << endl;
                            cout << "1. Display the price for a stock symbol" << endl;
                            cout << "2. Display the current portfolio" << endl;
                            cout << "3. Buy shares" << endl;
                            cout << "4. Sell shares" << endl;
                            cout << "5. View a graph for the portfolio value" << endl;
                            cout << "6. View transaction history" << endl;
                            cout << "7. Return to previous menu" << endl;
                            cout << "Option: ";
                            cin >> choice;
                            break;
                        case 1: // get a price
                            stockAccount.showPrice();
                            choice = 0;
                            break;
                        case 2: // print current portfolio
                            stockAccount.displayPortfolio();
                            choice = 0;
                            break;
                        case 3: // buy
                        {
                            double cash = stockAccount.buyShare();
                            bankAccount.setCashBalance(cash);
                            choice = 0;
                            break;
                        }
                        case 4: // sell
                        {
                            double cash = stockAccount.sellShare();
                            bankAccount.setCashBalance(cash);
                            choice = 0;
                            break;
                        }
                        case 5: // view graph
                            cout << "nothing here right now" << endl;
                            stockAccount.viewGraph();
                            choice = 0;
                            break;
                        case 6: // view history
                            stockAccount.viewHistory();
                            choice = 0;
                            break;
                        default:
                            cout << "We do not have that option." << endl;
                            choice = 0;
                            break;
                    }
                }
                todo = 0; // return to the main menu
                break;
            }
            case 2: // Bank Account
            {
                choice = 0;
                while (choice != 5) {
                    switch (choice) {
                        case 0: // show the menu
                            cout << endl;
                            cout << "Please select an option:" << endl;
                            cout << "1. View account balance" << endl;
                            cout << "2. Deposit money" << endl;
                            cout << "3. Withdraw money" << endl;
                            cout << "4. Print out history" << endl;
                            cout << "5. Return to previous menu" << endl;
                            cout << "Option: ";
                            cin >> choice;
                            break;
                        case 1: // view balance
                            bankAccount.viewBalance();
                            choice = 0;
                            break;
                        case 2: // deposit
                        {
                            double cash = bankAccount.deposit();
                            stockAccount.setCashBalance(cash);
                            choice = 0;
                            break;
                        }
                        case 3: // withdraw
                        {
                            double cash = bankAccount.withdraw();
                            stockAccount.setCashBalance(cash);
                            choice = 0;
                            break;
                        }
                        case 4: // print history
                            bankAccount.printHistory();
                            choice = 0;
                            break;
                        default:
                            cout << "We do not have that option." << endl;
                            choice = 0;
                            break;
                    }
                }
                todo = 0;  // return to the main menu
                break;
            }
            default:
                cout << "We do not have that option." << endl;
                todo = 0;
                break;
        }
    }
    cout << "Now Exit" << endl;
    return 0;
}