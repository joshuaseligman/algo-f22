#include <iostream>
#include <string>

#include "node.h"
#include "stack.h"
#include "queue.h"
#include "fileUtil.h"
#include "util.h"

// Function to test the Node class
void testNode() {
    // Create the nodes on the stack, so we do not have to delete later
    Node<std::string> n1("node 1");
    Node<std::string> n2("node 2");
    Node<std::string> n3("node 3");

    // Set up the links
    n1.next = &n2;
    n2.next = &n3;

    // Print out the data of each node in the linked list
    Node<std::string>* cur = &n1;
    while (cur != nullptr) {
        std::cout << cur->data << std::endl;
        cur = cur->next;
    }
}

// Function to test the Stack class
void testStack() {
    // Create a stack and add some data to it
    Stack<char> stack;
    stack.push('h');
    stack.push('s');
    stack.push('o');
    stack.push('J');

    // Print out the letters as we remove them from the stack
    while (!stack.isEmpty()) {
        std::cout << stack.pop();
    }
    std::cout << std::endl;

    try {
        // This should throw an error
        stack.pop();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Function to test the Queue class
void testQueue() {
    // Create a queue and add some data to it
    Queue<char> queue;
    queue.enqueue('J');
    queue.enqueue('o');
    queue.enqueue('s');
    queue.enqueue('h');

    // Print out the letters as we remove them from the queue
    while (!queue.isEmpty()) {
        std::cout << queue.dequeue();
    }
    std::cout << std::endl;

    try {
        // This should throw an error
        queue.dequeue();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    std::cout << "----- Testing Node class -----" << std::endl;
    testNode();
    std::cout << std::endl;

    std::cout << "----- Testing Stack class -----" << std::endl;
    testStack();
    std::cout << std::endl;

    std::cout << "----- Testing Queue class -----" << std::endl;
    testQueue();
    std::cout << std::endl;

    try {
        // Read the file and store it in an array
        StringArr* data = readFile("magicitems.txt");

        // Print out each row
        for (int i = 0; i < data->length; i++) {
            std::cout << data->arr[i] << std::endl;
        }

        // Clean up memory
        delete data;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}