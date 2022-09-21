#include <iostream>

#include "fileUtil.h"
#include "util.h"
#include "sortsAndShuffles.h"

int main() {
    // Read in the magic items
    StringArr* magicItems = readFile("magicitems.txt");

    // Shuffle them and perform selection sort
    knuthShuffle(magicItems);
    std::cout << selectionSort(magicItems) << std::endl;
    
    // Print out the list to make sure everything is in order
    for (int i = 0; i < magicItems->length; i++) {
        std::cout << magicItems->arr[i] << std::endl;
    }

    // Memory management
    delete magicItems;

    return 0;
}