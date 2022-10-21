#pragma once

#include "node.h"

template <typename T>
class List {
private:
    // Head points to the front of the list
    Node<T>* head;
    
    // Tail points to the end of the list
    Node<T>* tail;

    // The current size of the list
    int size;
public:
    // Constructor for the list
    List();

    ~List();

    // Append adds a new element to the list
    void enqueue(Node<T>* newNode);

    // Removes the front element from the list
    Node<T>* dequeue();

    // Removes a node from the list
    void remove(T removeData);

    // isEmpty checks to see if the list is empty
    bool isEmpty();

    // Prints the entire list out
    void printList();

    // Getter for the size of the list
    int getSize();

    // Getter for the head
    Node<T>* getHead();
};