#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <string>

#include "util.h"
#include "fileUtil.h"
#include "sortsAndShuffles.h"
#include "searches.h"

int main() {
    StringArr* magicItems = readFile("magicItems.txt");

    // A set for the random items we want to find. Sets prevent duplicates, so no need to worry about that
    std::set<std::string> randomItems;

    srand(time(NULL));
    
    // Find elements until we have 42 random elements
    while(randomItems.size() < 42) {
        int randomIndex = rand() % magicItems->length;
        randomItems.insert(magicItems->arr[randomIndex]);
    }

    // Perform a linear search on the elements
    for (auto it = randomItems.begin(); it != randomItems.end(); it++) {
        int comparisons = 0;
        int pos = linearSearch(magicItems, *it, &comparisons);
        std::cout << *it << ": " << pos << "; " << comparisons << std::endl;
    }

    // Test case for an element that doesn't exist
    int comparisons = 0;
    std::cout << "test" << ": " << linearSearch(magicItems, "test", &comparisons) << "; " << comparisons << std::endl;

    // Memory management
    delete [] magicItems->arr;
    delete magicItems;
}