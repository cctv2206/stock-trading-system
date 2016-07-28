//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#include "Stock_Kai.h"
#include "Account_Kai.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;

std::vector<std::string> split(std::string ,std::string ); // split the string

StockAccount::StockAccount(double cash) // -------------- constructor
: Account()
{
    setCashBalance(cash);
    // ------------------ get the results 1 and 2
    ifstream myfile1 ("Results_1.txt");
    string line1;
    ifstream myfile2 ("Results_2.txt");
    string line2;
    if (myfile1.is_open() && myfile2.is_open()) // if it is open
    {

        while (getline(myfile1, line1) && getline(myfile2, line2)) {
            vector<string> result1 = split(line1, "\t");
            vector<string> result2 = split(line2, "\t");
            vector<string> thisline;
            thisline.push_back(result1[0]);
            thisline.push_back(result1[1]);
            thisline.push_back(result2[1]);
            stockPrices.push_back(thisline);
        }
        myfile1.close();
        myfile2.close();
    }
    else // can not open results
    {
        cout << "can not find the Results" << endl;
    
    }
    // ------------------ get the results 1 and 2 ends
    
    // ------------------ get the currrent portfolio
    portfolioList = LinkedList();
    ifstream portfolioFile("portfolio.txt");
    string portfolioLine;
    if (portfolioFile.is_open()) // read the last file
    {
        //cout << "opened the portfolio" << endl;
        while(getline(portfolioFile, portfolioLine))
        {
            vector<string> result =split(portfolioLine, "\t");
            if (result[0].compare("") == 0)
            {
                cout << "You don't have any portfolio yet." << endl;
                break;
            }
            portfolioList.addToEnd(new Node(result[0], stoi(result[1])));
        }
        portfolioFile.close();
        
    }
    else // new user, creat a portfolio file
    {
        //creat a new file
        ofstream newfile;
        newfile.open("portfolio.txt", ios::trunc);
        newfile << "" << endl;
        //cout << "Welcome new user" << endl;
        newfile.close();
    }
    
    // initialize the total portfolio file
    ifstream check("totalValue.txt");
    if (!check.is_open()) {
        ofstream newTotalFile;
        newTotalFile.open("totalValue.txt", ios::trunc);
        time_t seconds;
        seconds = time(NULL);
        tm * timeinfo;
        timeinfo = localtime(&seconds);
        newTotalFile << 10000 << "\t" << asctime(timeinfo) << endl;
    }
    
}

StockAccount::~StockAccount() //destructor
{
    // write the portfolio
    ofstream portFile;
    portFile.open("portfolio.txt", ios::trunc);
    Node *currentPtr = portfolioList.getHead();
    while (currentPtr!=0) {
        portFile << currentPtr->getName() << "\t" << currentPtr->getNumber() << endl;
        currentPtr = currentPtr->getNext();
    }
    portFile.close();
    
    // write the current cash balance
    ofstream cashFile;
    cashFile.open("cashBalance.txt", ios::trunc);
    cashFile << "$" << getCashBalance() << endl;
    cashFile.close();
    
    // write the total portfolio value
    double total = getCashBalance();
    currentPtr = portfolioList.getHead();
    while (currentPtr != 0) {
        total += currentPtr->getNumber() * getPrice(currentPtr->getName());
        currentPtr = currentPtr->getNext();
    }
    
    ofstream newTotalFile;
    newTotalFile.open("totalValue.txt", ios::app);
    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    newTotalFile << total << "\t" << asctime(timeinfo) << endl;
    
}


void StockAccount::showPrice()
{
    string name;
    cout << "Please enter the stock symbol:";
    cin >> name;
    for (int i = 0;i<stockPrices.size();i++)
    {
        if (name.compare(stockPrices[i][0]) == 0) // check if we have the stock
        {
            time_t seconds;
            time(&seconds);
            srand((unsigned int) seconds);
            cout <<"Company Symbol" << "\t Price per share" << endl;
            cout << name << "\t\t\t $" << stockPrices[i][rand()%2 +1] << endl;
            return;
        }
    }
    cout << "We don't have this stock." << endl;
}

double StockAccount::getPrice(string name)
{
    for (int i = 0;i<stockPrices.size();i++)
    {
        if (name.compare(stockPrices[i][0]) == 0) // find the stock
        {
            time_t seconds;
            time(&seconds);
            srand((unsigned int) seconds);
            return stod(stockPrices[i][rand()%2 +1]);
        }
    }
    return 0;
}

void StockAccount::displayPortfolio()
{
    cout << "Cash Balance: $" << getCashBalance() << endl;
    // check if we have the portfolio
    if (portfolioList.isEmpty()) {
        cout << "You do not have any Portfolio yet." << endl;
        return;
    }
    cout << setw(20) << "Company-Symbol" << setw(10) << "Number" << setw(20) << "Price-per-share" << setw(10) << "Total value" << endl;
    Node *currentPtr = portfolioList.getHead();
    while (currentPtr != 0) {
        cout << setw(20) << currentPtr->getName() << setw(10) << currentPtr->getNumber() << setw(20) << getPrice(currentPtr->getName())<< setw(10) << currentPtr->getNumber()*getPrice(currentPtr->getName())<< endl;
        currentPtr = currentPtr->getNext();
    }
    cout << endl;
}

double StockAccount::buyShare()
{
    double cash = getCashBalance();
    cout << "Please enter the stock symbol you wish to purchase:";
    string name;
    cin >> name;
    // get the current price. if not a stock, return
    double price = getPrice(name);
    if (price == 0){
        cout << "Transaction Failed: We do not have that stock." << endl;
        return cash;
    }
    cout << "Please enter the number of shares:";
    int number;
    cin >> number;
    cout << "Please enter the maximum amount you are willing to pay per share:";
    double max;
    cin >> max;
    //check the price
    if (price > max) {
        cout << "Transaction Failed: The current price of the stock is too high." << endl;
        return cash;
    }
    //check the money
    if (cash < price*number) {
        cout << "Transaction Failed: You do not have enough money" << endl;
        return cash;
    }
    // ok to buy
    // check if it is a new stock
    Node *currentPtr = portfolioList.getHead();
    bool flag = false;
    while (currentPtr != 0) {
        if (currentPtr->getName().compare(name) == 0) {
            currentPtr->setNumber(currentPtr->getNumber() + number);
            flag = true;
            break;
        }
        currentPtr = currentPtr->getNext();
    }
    if (!flag) {
        portfolioList.addToEnd(new Node(name, number));
    }
    setCashBalance(cash-price*number);
    
    // ---  write the transaction history
    ifstream check("stock_transaction_history.txt");// check if the history file exist
    if (!check.is_open()) {
        //creat history file
        ofstream newhistoryFile;
        newhistoryFile.open("stock_transaction_history.txt", ios::trunc);
        newhistoryFile << setw(10) << "Event" << setw(10) << "Symbol" << setw(10) << "Number" << setw(10) << "Price" << setw(10) << "Value" << setw(15) << "Time" << endl;
        newhistoryFile.close();
    }
    //write
    ofstream historyFile;
    historyFile.open("stock_transaction_history.txt", ios::app);
    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    historyFile << setw(10) << "BUY" << setw(10) << name << setw(10) << number << setw(10) << price << setw(10) << price*number << setw(30) << asctime(timeinfo) << endl;
    historyFile.close();
    
    return getCashBalance();
}

double StockAccount::sellShare()
{
    double cash = getCashBalance();
    cout << "Please enter the stock symbol you wish to sell:";
    string name;
    cin >> name;
    //check if in the portfolio
    Node *currentPtr = portfolioList.getHead();
    bool flag = false;
    while (currentPtr != 0) {
        if (currentPtr->getName().compare(name) == 0) { // ---- find the stock
            flag = true;
            cout << "Please enter the number of shares:";
            int number;
            cin >> number;
            // check the number of share
            if (currentPtr->getNumber() < number) {
                cout << "Transaction Failed: You do not have enough share to sell." << endl;
                return cash;
            }
            cout << "Please enter the minimum amount you are willing to sell per share:";
            double min;
            cin >> min;
            // check the price
            double price = getPrice(name);
            if (price < min) {
                cout << "Transaction Failed: The current price of the stock is too low." << endl;
                return cash;
            }
            // all good, ready to sell
            currentPtr->setNumber(currentPtr->getNumber()-number);
            setCashBalance(cash + price*number);
            //delete the stock if sell all of it
            if (currentPtr->getNumber() == 0) {
                portfolioList.removeNodeFromList(name);
            }
            
            // write the transaction history
            ofstream historyFile;
            historyFile.open("stock_transaction_history.txt", ios::app);
            time_t seconds;
            seconds = time(NULL);
            tm * timeinfo;
            timeinfo = localtime(&seconds);
            historyFile << setw(10) << "SELL" << setw(10) << name << setw(10) << number << setw(10) << price << setw(10) << price*number << setw(30) << asctime(timeinfo) << endl;
            historyFile.close();
            
            return getCashBalance();
        }
        currentPtr = currentPtr->getNext();
    }
    if (!flag) {
        cout << "Transaction Failed: You do not have that stock." << endl;
        return cash;
    }
    return getCashBalance();
}

void StockAccount::viewHistory()
{
    ifstream check("stock_transaction_history.txt");// check if the history file exist
    if (!check.is_open()) {
        cout << "You don't have any transactions yet" << endl;
        return;
    }
    ifstream historyFile("stock_transaction_history.txt"); // if exists
    string historyLine;
    cout << "\t\t TRANSACTION HISTORY" << endl;
    cout << endl;
    while(getline(historyFile, historyLine))
    {
        cout << historyLine << endl; // print out every line
    }
    
}

void StockAccount::viewGraph()
{
    ifstream check("totalValue.txt");// check if the total value file exist
    if (!check.is_open()) {
        cout << "You don't have any transactions yet" << endl;
        return;
    }
    ifstream totalFile("totalValue.txt");
    string totalLine;

    vector<double> totalValue;
    while(getline(totalFile, totalLine))
    {
        vector<string> result =split(totalLine, "\t");
        if (result[0].compare("") == 0) {
            continue;
        }
        totalValue.push_back(stod(result[0]));
        //cout << totalLine << endl;
    }
    double *a = &totalValue[0];
    for (int i = 0; i < totalValue.size(); i++) // print out the values
    {
        cout << a[i] << endl;
    }
    
}
