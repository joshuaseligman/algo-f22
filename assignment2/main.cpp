#include <iostream>
#include <chrono>
#include <math.h>

#include "fileUtil.h"
#include "util.h"
#include "sortsAndShuffles.h"

// Function to run and print results of a sorting algorithm
void runSort(int (*sort)(StringArr*), StringArr* input, std::string sortName, bool shuffle) {
    // Shuffle them and perform the sort
    // Time calculations from https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    if (shuffle) {
        knuthShuffle(input);
    }
    auto start = std::chrono::high_resolution_clock::now();
    int numComparisons = sort(input);
    auto stop = std::chrono::high_resolution_clock::now();
    // We need to cast the difference in the stop and start times to nanoseconds
    long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

    // Print out the results of the sort
    std::cout << sortName << " Sort" << std::endl;
    std::cout << "Comparisons: " << numComparisons << std::endl;
    std::cout << "Time       : " << totalTime << " ns" << std::endl << std::endl;;

}

int main() {
    // Read in the magic items
    StringArr* magicItems = readFile("magicitems.txt");

    // Output some basic stats for comparison to O(n^2) and O(n * log(n)) growth functions
    std::cout << "n         : " << magicItems->length << std::endl;
    std::cout << "n^2       : " << magicItems->length * magicItems->length << std::endl;
    std::cout << "n * log(n): " << magicItems->length * log2(magicItems->length) << std::endl << std::endl;

    std::cout << "666 Magic Items, shuffled" << std::endl;
    // Run and analyze selection sort
    runSort(selectionSort, magicItems, "Selection", true);

    // Run and analyze insertion sort
    runSort(insertionSort, magicItems, "Insertion", true);

    runSort(mergeSort, magicItems, "Merge", true);

    std::cout << "20 Yankees Greats, sorted" << std::endl;
    StringArr* sortedYankees = readFile("yankeesGreatsSorted.txt");
    runSort(selectionSort, sortedYankees, "Selection", false);
    runSort(insertionSort, sortedYankees, "Insertion", false);
    runSort(mergeSort, sortedYankees, "Merge", false);

    std::cout << "20 Yankees Greats, reversed" << std::endl;
    StringArr* reversedYankees = readFile("yankeesGreatsReversed.txt");
    runSort(selectionSort, reversedYankees, "Selection", false);
    delete reversedYankees;

    reversedYankees = readFile("yankeesGreatsReversed.txt");
    runSort(insertionSort, reversedYankees, "Insertion", false);
    delete reversedYankees;

    reversedYankees = readFile("yankeesGreatsReversed.txt");
    runSort(mergeSort, reversedYankees, "Merge", false);
    delete reversedYankees;

    std::cout << "Empty List" << std::endl;
    StringArr* emptyList = readFile("emptyList.txt");
    runSort(selectionSort, emptyList, "Selection", false);
    runSort(insertionSort, emptyList, "Insertion", false);
    runSort(mergeSort, emptyList, "Merge", false);


    // Print out the list to make sure everything is in order
    // for (int i = 0; i < magicItems->length; i++) {
    //     std::cout << magicItems->arr[i] << std::endl;
    // }

    // Memory management
    delete magicItems;
    delete sortedYankees;

    return 0;
}