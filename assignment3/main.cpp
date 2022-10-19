#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <string>

#include "util.h"
#include "fileUtil.h"
#include "sortsAndShuffles.h"

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

    // Print the random elements for now
    for (auto it = randomItems.begin(); it != randomItems.end(); it++) {
        std::cout << *it << std::endl;
    }

    // Memory management
    delete [] magicItems->arr;
    delete magicItems;
}