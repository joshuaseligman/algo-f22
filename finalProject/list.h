#pragma once

#include "node.h"

// Wrapper class for a linked list with more functionality for modifying the list and its contents
template <typename T>
class List {
private:
    // Head points to the front of the list
    Node<T>* head;
    
    // Tail points to the end of the list
    Node<T>* tail;
public:
    // Constructor for the list
    List();

    ~List();

    // Append adds a new element to the list
    void append(Node<T>* newNode);

    // Equivalent of dequeue for a queue
    Node<T>* removeHead();

    // isEmpty checks to see if the list is empty
    bool isEmpty();

    // Prints the entire list out
    void printList();
};