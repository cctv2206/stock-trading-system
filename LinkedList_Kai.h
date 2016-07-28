//
// Name : Kai Kang
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
// Final Project : Account Management System
// Date of submission : 05/06/2015
//

#ifndef LinkedList_Kai_h
#define LinkedList_Kai_h

#include <string>
using namespace std;
using std::string;


class Node{
    friend class LinkedList;
public:
    Node(string name, int no) // constructor
    :itemName(name), itemNo(no)
    {
        this->next=NULL;
        this->prev=NULL;
    }
    string getName(){ // get name
        return itemName;
    }
    int getNumber(){return itemNo;} // get number
    Node* getNext(){return next;} // get next
    void setNumber(int number){itemNo = number;} // set number
    
private:
    string itemName;
    int itemNo;
    Node *next;
    Node *prev;
    
};

class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    Node* getHead();
    int size() const;
    void addToStart(Node *);
    void addToEnd(Node *);
    void printList();
    bool isEmpty() const;
    bool removeFromStart();
    bool removeFromEnd();
    void removeNodeFromList(int);
    void removeNodeFromList(string);
private:
    Node *myHead;
    Node *myTail;
    int mySize;
};


#endif /* defined(__linkedList__LinkedList_Kai__) */