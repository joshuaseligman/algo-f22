#include <string>

#include "stack.h"
#include "node.h"

// Instantiate the stack with the top pointing to nothing
Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    // Since the nodes were created on the heap, we have to make sure everything is cleared from memory
    while (!isEmpty()) {
        pop();
    }
}

// Creates a new node and adds it to the stack
void Stack::push(std::string newData) {
    Node* newNode = new Node(newData);
    // Set the next first so we do not lose the rest of the stack
    newNode->next = top;
    top = newNode;
}

// Removes the top node from the stack
std::string Stack::pop() {
    if (isEmpty()) {
        // Throw an exception if the stack is already empty
        throw std::invalid_argument("Tried to pop from an empty stack.");
    } else {
        // We need to collect the data in the node before removing it from the stack
        Node* topNode = top;
        std::string topData = topNode->data;
        top = top->next;

        // Since the node was created on the heap, we have to free it from memory
        delete topNode;
        return topData;
    }
}

// Checks to see if the stack is empty or not
bool Stack::isEmpty() {
    return top == nullptr;
}