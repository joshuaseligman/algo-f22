#pragma once

#include "node.h"

template <typename T>
class Queue {
private:
    // Head points to the front of the queue
    Node<T>* head;
    
    // Tail points to the end of the queue
    Node<T>* tail;
public:
    // Constructor for the queue
    Queue();

    ~Queue();

    // Append adds a new element to the queue
    void enqueue(Node<T>* newNode);

    // Removes the front element from the queue
    Node<T>* dequeue();

    // isEmpty checks to see if the queue is empty
    bool isEmpty();

    // Prints the entire queue out
    void printQueue();
};