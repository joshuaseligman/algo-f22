#pragma once

#include "node.h"
#include <string>

class HashTable {
    public:
        // The array for the hashtable
        Node<std::string>** table;

        // Store the size of the hash table
        int size;

        // Hash tables will take in the size of the array to store
        HashTable(int size);

        ~HashTable();

        // Returns if the value is in the hash table
        bool get(std::string value);

        // Puts the value in the hash table
        void put(std::string value);

        // Prints out the entire hash table
        void printHashTable();
    private:
        // The hash function that is used for the 
        int hash(std::string value);
};
