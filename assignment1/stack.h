#pragma once

#include "node.h"

template <typename T>
class Stack {
private:
    // Top points to the top of the stack
    Node<T>* top;
public:
    // We need a constructor and destructor
    Stack();
    ~Stack();

    // Push adds a new element to the stack
    void push(T newData);

    // Pop removes the top element from the stack
    T pop();

    // isEmpty checks to see if the stack is empty
    bool isEmpty();
};