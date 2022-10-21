#include "hashTable.h"

#include <string>
#include <iostream>
#include "node.h"

HashTable::HashTable(int size) {
    // Save the size
    this->size = size;

    // Create the new array
    table = new Node<std::string>*[size];

    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    // Delete all nodes in the table
    for (int i = 0; i < size; i++) {
        Node<std::string>* cur = table[i];

        while (cur != nullptr) {
            // Get the next element to save while the current element gets deleted
            Node<std::string>* next = cur->next;
            delete cur;

            // Move the cur pointer along
            cur = next;
        }
    }

    delete [] table;
}

bool HashTable::get(std::string value, int* comparisons) {
    // Increment the number of comparisons off the bat
    if (comparisons != nullptr) {
        (*comparisons)++;
    }

    // Compute the hash function
    int index = hash(value);

    // Assume the value isn't in the table
    bool found = false;

    // Start at the head of the list
    Node<std::string>* cur = table[index];

    while (!found && cur != nullptr) {
        // Determine if the value was found
        if (cur->data.compare(value) == 0) {
            found = true;
        } else {
            // Move to the next element
            cur = cur->next;
        }

        // A comparison was made
        if (comparisons != nullptr) {
            (*comparisons)++;
        }
    }
    return found;
}

void HashTable::put(std::string value) {
    // Generate the hash
    int index = hash(value);

    // Create a new node for the table
    Node<std::string>* newNode = new Node<std::string>(value);

    // If the table entry is not empty, set the next pointer of the new node
    if (table[index] != nullptr) {
        newNode->next = table[index];
    }
    
    // Place the new node at the head of the list
    table[index] = newNode;
}

int HashTable::hash(std::string value) {
    // Keep a runnning sum of the ordinal codes seen so far
    int letterTotal = 0;

    // Iterate through each character in the word
    for (int i = 0; i < value.length(); i++) {
        char character = value[i];
        if (character >= 'a' && character <= 'z') {
            // Adjust the character to make it uppercase by taking the difference between
            // the start of the lowercase letters and the start of the uppercase letters
            character -= 'a' - 'A';
        }

        // Add the ordinal value to the running sum
        letterTotal += character;
    }
    
    // Hash code is the sum of the ordinal values mod the size of the array
    int hashCode = letterTotal % size;
    return hashCode;
}

void HashTable::printHashTable() {
    // Iterate through the table
    for (int i = 0; i < size; i++) {
        Node<std::string>* cur = table[i];

        if (cur != nullptr) {
            // Print out the entire list
            while (cur != nullptr) {
                std::cout << cur->data << " -> ";
                cur = cur->next;
            }
        }

        // All lists end with a nullptr
        std::cout << "nullptr" << std::endl;
    }
}