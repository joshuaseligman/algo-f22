#include <string>
#include <iostream>

#include "stack.h"
#include "node.h"

// Instantiate the stack with the top pointing to nothing
template <typename T>
Stack<T>::Stack() {
    top = nullptr;
}

// Creates a new node and adds it to the stack
template <typename T>
void Stack<T>::push(Node<T>* newNode) {
    // Set the next first so we do not lose the rest of the stack
    newNode->next = top;
    top = newNode;

    // printStack();
}

// Removes the top node from the stack
template <typename T>
Node<T>* Stack<T>::pop() {
    if (isEmpty()) {
        // Throw an exception if the stack is already empty
        throw std::invalid_argument("Stack underflow exception. Tried to pop from an empty stack.");
    } else {
        // We need to collect the data in the node before removing it from the stack
        Node<T>* topNode = top;
        top = top->next;

        // We have to remove whatever next is pointing to because the node is no longer
        // a part of the linked list for the stack
        topNode->next = nullptr;

        return topNode;
    }
}

// Checks to see if the stack is empty or not
template <typename T>
bool Stack<T>::isEmpty() {
    return top == nullptr;
}

template <typename T>
void Stack<T>::printStack() {
    // Get the top of the stack and iterate through, printing the data in each node
    Node<T>* cur = top;
    while (cur != nullptr) {
        std::cout << cur->data << " -> ";
        cur = cur->next;
    }
    // Finish the queue printing
    std::cout << "nullptr" << std::endl;
}

// Define acceptable data types that the Stack can accept for the template
template class Stack<std::string>;