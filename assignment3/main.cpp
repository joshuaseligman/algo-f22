#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <string>
#include <stdio.h>

#include "util.h"
#include "fileUtil.h"
#include "sortsAndShuffles.h"
#include "searches.h"
#include "hashTable.h"

void runSearch(int (*search)(StringArr*, std::string, int*), StringArr* input, std::set<std::string> targets, std::string searchName) {
    std::cout << searchName << std::endl;

    int totalComparisons = 0;

    // Loop through each target
    for (auto it = targets.begin(); it != targets.end(); it++) {
        int comparisons = 0;
        int pos = search(input, *it, &comparisons);

        std::cout << *it << " - position: " << pos << "; comparisons: " << comparisons << std::endl;

        totalComparisons += comparisons;
    }

    double average = (double) totalComparisons / targets.size();
    printf("Average comparisons: %.2f\n", average);
}

int main() {
    StringArr* magicItems = readFile("magicItems.txt");

    // A set for the random items we want to find. Sets prevent duplicates, so no need to worry about that
    std::set<std::string> randomItems;

    srand(time(NULL));
    
    // Find elements until we have 42 random elements
    while (randomItems.size() < 42) {
        int randomIndex = rand() % magicItems->length;
        randomItems.insert(magicItems->arr[randomIndex]);
    }

    // Sort the magic items to get the same position for both linear and binary search
    quickSort(magicItems);

    runSearch(linearSearch, magicItems, randomItems, "Linear Search");
    std::cout << std::endl;

    runSearch(binarySearch, magicItems, randomItems, "Binary Search (recursion)");
    std::cout << std::endl;

    // Single edge cases
    std::cout << "Linear search edge cases:" << std::endl; 

    // Test case for an element that doesn't exist
    int comparisons = 0;
    std::cout << "test - position: " << linearSearch(magicItems, "test", &comparisons) << "; comparisons: " << comparisons << std::endl << std::endl;

    std::cout << "Binary search edge cases:" << std::endl;

    // Test case for the first element in the list
    comparisons = 0;
    std::cout << magicItems->arr[0] << " - position: " << binarySearch(magicItems, magicItems->arr[0], &comparisons) << "; comparisons: " << comparisons << std::endl;

    // Test case for the last element in the list
    comparisons = 0;
    std::cout << magicItems->arr[magicItems->length - 1] << " - position: " << binarySearch(magicItems, magicItems->arr[magicItems->length - 1], &comparisons) << "; comparisons: " << comparisons << std::endl;

    // Test case for an element that doesn't exist
    comparisons = 0;
    std::cout << "test - position: " << binarySearch(magicItems, "test", &comparisons) << "; comparisons: " << comparisons << std::endl;
    
    std::cout << std::endl;

    // Create a hash table of size 250
    HashTable h(250);

    // Put the magic items in the hash table
    for (int i = 0; i < magicItems->length; i++) {
        h.put(magicItems->arr[i]);
    }
    
    // Initialize total comparisons to 0
    int totalComparisons = 0;

    // Try to get all of the 42 selected items
    for (auto it = randomItems.begin(); it != randomItems.end(); it++) {
        int comparisons = 0;

        // Try to get the item
        bool found = h.get(*it, &comparisons);

        std::cout << *it << " - found: " << found << "; comparisons: " << comparisons << std::endl;

        // Add to the total
        totalComparisons += comparisons;
    }

    // Print a summary
    double average = (double) totalComparisons / randomItems.size();
    printf("Average comparisons: %.2f\n", average);

    std::cout << std::endl;
    
    // Try to get something that isn't in the table
    comparisons = 0;
    std::cout << "test - found: " << h.get("test", &comparisons) << "; comparisons: " << comparisons << std::endl;

    // Memory management
    delete [] magicItems->arr;
    delete magicItems;
}