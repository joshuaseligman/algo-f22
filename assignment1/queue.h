#pragma once

#include "node.h"

template <typename T>
class Queue {
private:
    // Head points to the front of the queue
    Node<T>* head;
public:
    // We need a constructor and destructor
    Queue();
    ~Queue();

    // Enqueue adds a new element to the queue
    void enqueue(T newData);

    // Dequeue removes the front element from the queue
    T dequeue();

    // isEmpty checks to see if the queue is empty
    bool isEmpty();
};