#include <string>
#include <iostream>
#include <string.h>

#include "list.h"
#include "node.h"
#include "resident.h"
#include "hospital.h"

// Instantiate the list with the head pointing to nothing
template <typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;

    size = 0;
}

template <typename T>
List<T>::~List() {
    while (!isEmpty()) {
        Node<T>* n = dequeue();
        delete n;
    }
}

// Creates a new node and adds it to the list
template <typename T>
void List<T>::enqueue(Node<T>* newNode) {    
    if (isEmpty()) {
        // Immediately set the head and tail to be the new node if we are empty
        head = newNode;
        tail = newNode;
    } else {
        // Have the old tail to point to the new node and then update the pointer
        tail->next = newNode;
        tail = newNode;
    }

    // Increment the size
    size++;
}

template <typename T>
Node<T>* List<T>::dequeue() {
    if (isEmpty()) {
        // Throw an exception if the list is already empty
        throw std::invalid_argument("Tried to remove from an empty list.");
    } else {
        // We need to collect the data in the node before removing it from the list
        Node<T>* frontNode = head;
        head = head->next;
        if (head == nullptr) {
            // Tail has to become nullptr because the list is now empty
            tail = nullptr;
        }

        // We have to remove whatever next is pointing to because the node is no longer
        // a part of the linked list
        frontNode->next = nullptr;

        // Decrement the size
        size--;

        return frontNode;
    }
}

template <typename T>
void List<T>::remove(T removeData) {
    Node<T>* cur = head;
    Node<T>* prev = nullptr;

    // Remove the head element from the list
    if (cur->next == nullptr) {
        head = nullptr;
        tail = nullptr;

        delete cur;
    } else {
        // Go through the list until the end or until the element is found
        while (cur != nullptr && cur->data != removeData) {
            prev = cur;
            cur = cur->next;
        }

        if (cur != nullptr) {
            // If not at the end of the list, remove the node
            prev->next = cur->next;

            // Update the tail if needed
            if (prev->next == nullptr) {
                tail = prev;
            }

            // Memory management
            delete cur;
        }
    }
}

// Checks to see if the list is empty or not
template <typename T>
bool List<T>::isEmpty() {
    return head == nullptr;
}

template <typename T>
void List<T>::printList() {
    // Get the head of the list and iterate through, printing the data in each node
    Node<T>* cur = head;
    while (cur != nullptr) {
        if (strcmp(typeid(cur->data).name(), "P8Hospital") == 0) {
            std::cout << ((Hospital*)cur->data)->getName() << " -> ";
        } else if (strcmp(typeid(cur->data).name(), "P8Resident") == 0) {
            std::cout << ((Resident*)cur->data)->getName() << " -> ";
        } else {
            std::cout << cur->data << " -> ";
        }
        cur = cur->next;
    }
    // Finish the queue printing
    std::cout << "nullptr" << std::endl;
}

template <typename T>
int List<T>::getSize() {
    return size;
}

template <typename T>
Node<T>* List<T>::getHead() {
    return head;
}

// Define acceptable data types that the List can accept for the template
template class List<Hospital*>;
template class List<Resident*>;