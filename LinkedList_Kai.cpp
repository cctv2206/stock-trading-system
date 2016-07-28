//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#include "LinkedList_Kai.h"

#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

LinkedList::LinkedList()
: myHead(0), myTail(0)
{
    mySize = 0;
}

LinkedList::~LinkedList()
{}

int LinkedList::size() const
{
    return mySize;
}

Node* LinkedList::getHead()
{
    return myHead;
}

// add an item to the start
void LinkedList::addToStart(Node *newPtr)
{
    if (isEmpty()) {
        myHead = myTail = newPtr;
    }
    else
    {
        newPtr->next = myHead;
        myHead->prev = newPtr;
        myHead = newPtr;
    }
    mySize ++;
}

//add an item to the end
void LinkedList::addToEnd(Node *newPtr)
{
    if (isEmpty()) {
        myHead = myTail = newPtr;
    }
    else
    {
        myTail->next = newPtr;
        newPtr->prev = myTail;
        myTail = newPtr;
    }
    mySize ++;
}

//print the list
void LinkedList::printList()
{
    if (isEmpty()) {
        cout << "The list is empty." << endl;
        return;
    }
    cout << endl;
    cout << "Company-Symbol  Number  Price-per-share  Total value" << endl;
    Node *currentPtr = myHead;
    while (currentPtr != 0) {
        cout << currentPtr->itemName << "\t\t" << currentPtr->itemNo <<"\t\t" << endl;
        currentPtr = currentPtr->next;
    }
    cout << endl;
}

//check if the list is empty
bool LinkedList::isEmpty() const
{
    return myHead == 0;
}

// remove the item from start
bool LinkedList::removeFromStart()
{
    if (isEmpty()) {
        return false;
    }
    else if (myTail == myHead)
    {
        myHead = myTail = 0;
    }
    else
    {
        Node *currentPtr = myHead;
        myHead = myHead->next;
        myHead->prev = NULL;
        delete currentPtr;
    }
    mySize --;
    return true;
}

// remove the item from end
bool LinkedList::removeFromEnd()
{
    if (isEmpty()) {
        return false;
    }
    else if (myHead == myTail)
    {
        myHead = myTail = 0;
    }
    else
    {
        Node *currentPtr;
        currentPtr = myTail->prev;
        myTail = currentPtr;
        currentPtr = currentPtr->next;
        myTail->next = NULL;
        delete currentPtr;
    }
    mySize --;
    return true;
}

//remove the item of its number
void LinkedList::removeNodeFromList(int num)
{
    Node *currentPtr = myHead;
    if (myHead == myTail) {
        cout << "No such item in the list." << endl;
        return;
    }
    while (currentPtr->itemNo != num)
    {
        currentPtr = currentPtr->next;
        if (currentPtr == 0) {
            cout << "No such item in the list." << endl;
            return;
        }
    }
    if (currentPtr == myHead) {
        removeFromStart();
    }
    else if (currentPtr == myTail) {
        removeFromEnd();
    }
    else
    {
        Node *tempPtr = myHead;
        while (tempPtr->next != currentPtr) {
            tempPtr = tempPtr->next;
        }
        tempPtr->next = currentPtr->next;
        delete currentPtr;
    }
    mySize --;
}

//remove the item of its name
void LinkedList::removeNodeFromList(string name)
{
    Node *currentPtr = myHead;
    if (myHead == myTail) {
        cout << "No such item in the list." << endl;
        return;
    }
    while (currentPtr->itemName != name)
    {
        currentPtr = currentPtr->next;
        if (currentPtr == 0) {
            cout << "No such item in the list." << endl;
            return;
        }
    }
    if (currentPtr == myHead) {
        removeFromStart();
    }
    else if (currentPtr == myTail) {
        removeFromEnd();
    }
    else
    {
        Node *tempPtr1;
        Node *tempPtr2;
        tempPtr1 = currentPtr->prev;
        tempPtr2 = currentPtr->next;
        tempPtr1->next = tempPtr2;
        tempPtr2->prev = tempPtr1;
        delete currentPtr;
    }
    mySize --;
}
