#pragma once

#include "node.h"

template <typename T>
class Queue {
private:
    // Head points to the front of the queue
    Node<T>* head;
    
    // Tail points to the end of the queue (tradeoff to get O(1) enqueue)
    Node<T>* tail;

    // The size of the queue
    int size;

public:
    // We need a constructor and destructor
    Queue();

    // Enqueue adds a new element to the queue
    void enqueue(Node<T>* newNode);

    // Dequeue removes the front element from the queue
    Node<T>* dequeue();

    // isEmpty checks to see if the queue is empty
    bool isEmpty();

    // Prints the entire queue out
    void printQueue();

    // Getter for the size
    int getSize();
};