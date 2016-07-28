# stock-trading-system
This is a simple stock trading system implemented in C++.

This is also the final project for Programming Finance course.

## Functions

### Stock Account
1.  Display a price of a stock
2.	Display the current portfolio
3.  Buy shares
4.	Sell shares
5.	View the total portfolio value changing through time
 * Note: The code works fine under Windows yet having some trouble connecting Matlab with Xcode. I still store the total portfolio value in a txt file every time the program exits. So that I can still read the file and print out the values. You can see the values changing through the time.

6.	View transaction history

### Bank Account
1.	View the account balance
2.	Deposit money
3.	Withdraw money
4.	Print out history

## Data structures:
Doubly linked list for the stock portfolio.

Vectors for storing stock prices.

Array for trying to connect with the Matlab.

### TXT files:
1.	Results_1.txt and Results_2.txt: Contains stock prices.
2.	cashBalance.txt: Generated when first running the program. Contains the current Cash Balance. Will be updated every time the program exits.
3.	Portfolio.txt: Generated when first running the program. Contains the current portfolio (stock name and number of shares hold). Will be updated every time the program exits.
4.	Stock_transaction_history.txt: Generated when first making a transaction. Contains all the stock transaction history.
5.	Bank_transaction_history.txt: Generated when first making a transaction. Contains all the bank transaction history.
6.	totalValue.txt: Generated when first running the program. Contains all the values of total portfolio value of every time the program exits. The file will be updated every time the program exits.
