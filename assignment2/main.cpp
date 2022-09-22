#include <iostream>
#include <chrono>
#include <math.h>

#include "fileUtil.h"
#include "util.h"
#include "sortsAndShuffles.h"

int main() {
    // Read in the magic items
    StringArr* magicItems = readFile("magicitems.txt");

    // Output some basic stats for comparison to O(n^2) and O(n * log(n)) growth functions
    std::cout << "n         : " << magicItems->length << std::endl;
    std::cout << "n^2       : " << magicItems->length * magicItems->length << std::endl;
    std::cout << "n * log(n): " << magicItems->length * log2(magicItems->length) << std::endl << std::endl;

    // Shuffle them and perform selection sort
    // Time calculations from https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    knuthShuffle(magicItems);
    auto start = std::chrono::high_resolution_clock::now();
    int selectionComparisons = selectionSort(magicItems);
    auto stop = std::chrono::high_resolution_clock::now();
    // We need to cast the difference in the stop and start times to microseconds
    long selectionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    // Print out the results of the selection sort
    std::cout << "Selection Sort" << std::endl;
    std::cout << "Comparisons: " << selectionComparisons << std::endl;
    std::cout << "Time       : " << selectionTime << " μs" << std::endl;
    
    // Print out the list to make sure everything is in order
    // for (int i = 0; i < magicItems->length; i++) {
    //     std::cout << magicItems->arr[i] << std::endl;
    // }

    // Memory management
    delete magicItems;

    return 0;
}