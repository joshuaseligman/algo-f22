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
        if (isEmpty()) {
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
    // Make sure the list isn't already empty
    if (!isEmpty()) {
        Node<T>* cur = head;
        Node<T>* prev = nullptr;

        if (cur->next == nullptr) {
            // Remove the element from the list of size 1
            head = nullptr;
            tail = nullptr;

            delete cur;

            // Update the size
            size--;
        } else if (removeData == head->data) {
            // Set the new head
            head = head->next;
            delete cur;

            size--;
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

                // Update the size
                size--;
            }
        }
    }
}

template <typename T>
void List<T>::priorityAdd(Node<T>* data, int level) {
    // Add the resident immediately if the list is empty
    if (isEmpty()) {
        head = data;
        tail = data;

        size++;
    } else {
        Node<T>* cur = head;
        Node<T>* prev = nullptr;

        // Make sure we are dealing with residents
        if (strcmp(typeid(cur->data).name(), "P8Resident") == 0) {
            // Convert the data to a Resident
            Resident* dataRes = (Resident*) data->data;

            // Boolean to see if the new node has been placed in the list yet
            bool placed = false;

            // Continue until the end of the list is hit
            while (cur != nullptr && !placed) {
                // Get the current node resident
                Resident* curRes = (Resident*) cur->data;

                // See if the resident is in the right place
                if (dataRes->compare(curRes, level) <= 0) {
                    // Place the new node in the list
                    data->next = cur;
                    if (prev == nullptr) {
                        // Update the head if needed
                        head = data;
                    } else {
                        // Insert the node into the list
                        prev->next = data;
                    }
                    placed = true;
                }
                prev = cur;
                cur = cur->next;
            }

            if (!placed) {
                // Place the node at the end of the list
                prev->next = data;
            }

            size++;
        } else {
            throw std::invalid_argument("Tried to use priority add for a Hospital list. Must use residents.");
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