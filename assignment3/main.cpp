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

void runSearch(int (*search)(StringArr*, std::string, int*), StringArr* input, std::set<std::string> targets, std::string searchName) {
    std::cout << searchName << " Search" << std::endl;

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

    runSearch(linearSearch, magicItems, randomItems, "Linear");
    std::cout << std::endl;

    quickSort(magicItems);

    runSearch(binarySearch, magicItems, randomItems, "Binary");
    std::cout << std::endl;

    // Test case for an element that doesn't exist
    int comparisons = 0;
    std::cout << "test - position: " << linearSearch(magicItems, "test", &comparisons) << "; comparisons: " << comparisons << std::endl;
    comparisons = 0;
    std::cout << "test - position: " << binarySearch(magicItems, "test", &comparisons) << "; comparisons: " << comparisons << std::endl;


    // Memory management
    delete [] magicItems->arr;
    delete magicItems;
}