#pragma once

#include "node.h"

class Queue {
private:
    // Head points to the front of the queue
    Node* head;
public:
    // We need a constructor and destructor
    Queue();
    ~Queue();

    // Enqueue adds a new element to the queue
    void enqueue(std::string newData);

    // Dequeue removes the front element from the queue
    std::string dequeue();

    // isEmpty checks to see if the queue is empty
    bool isEmpty();
};