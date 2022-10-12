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
}

template <typename T>
List<T>::~List() {
    while (!isEmpty()) {
        Node<T>* n = removeHead();
        delete n;
    }
}

// Creates a new node and adds it to the list
template <typename T>
void List<T>::append(Node<T>* newNode) {    
    if (isEmpty()) {
        // Immediately set the head and tail to be the new node if we are empty
        head = newNode;
        tail = newNode;
    } else {
        // Have the old tail to point to the new node and then update the pointer
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T>
Node<T>* List<T>::removeHead() {
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

        return frontNode;
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
        } else {
            std::cout << cur->data << " -> ";
        }
        cur = cur->next;
    }
    // Finish the list printing
    std::cout << "nullptr" << std::endl;
}

// Define acceptable data types that the List can accept for the template
template class List<Hospital*>;
template class List<Resident*>;