#pragma once

#include "node.h"

template <typename T>
class Stack {
private:
    // Top points to the top of the stack
    Node<T>* top;
public:
    // We need a constructor
    Stack();

    // Push adds a new element to the stack
    void push(Node<T>* newNode);

    // Pop removes the top element from the stack
    Node<T>* pop();

    // isEmpty checks to see if the stack is empty
    bool isEmpty();

    // Prints the stack out
    void printStack();
};