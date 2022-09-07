#include <string>

#include "queue.h"
#include "node.h"

// Instantiate the queue with the head pointing to nothing
Queue::Queue() {
    head = nullptr;
}

Queue::~Queue() {
    // Since the nodes were created on the heap, we have to make sure everything is cleared from memory
    while (!isEmpty()) {
        dequeue();
    }
}

// Creates a new node and adds it to the queue
void Queue::enqueue(std::string newData) {
    Node* newNode = new Node(newData);
    
    if (isEmpty()) {
        // Immediately set the head to be the new node if we are empty
        head = newNode;
    } else {
        // Traverse to the back of the queue
        Node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        // Insert the new node in the back of the queue
        cur->next = newNode;
    }
}

// Removes the front node from the queue
std::string Queue::dequeue() {
    if (isEmpty()) {
        // Throw an exception if the queue is already empty
        throw std::invalid_argument("Tried to dequeue from an empty queue.");
    } else {
        // We need to collect the data in the node before removing it from the queue
        Node* frontNode = head;
        std::string frontData = frontNode->data;
        head = head->next;

        // Since the node was created on the heap, we have to free it from memory
        delete frontNode;
        return frontData;
    }
}

// Checks to see if the queue is empty or not
bool Queue::isEmpty() {
    return head == nullptr;
}