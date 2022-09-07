#pragma once

#include "node.h"

class Stack {
private:
    // Top points to the top of the stack
    Node* top;
public:
    // We need a constructor and destructor
    Stack();
    ~Stack();

    // Push adds a new element to the stack
    void push(std::string newData);

    // Pop removes the top element from the stack
    std::string pop();

    // isEmpty checks to see if the stack is empty
    bool isEmpty();
};