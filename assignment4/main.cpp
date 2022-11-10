#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"
#include "binarySearchTree.h"
#include "binaryTreeNode.h"

#include "sortsAndShuffles.h"

#include "graphGenerator.h"

int main() {
    // Do the graphs stuff
    StringArr* graphFile = readFile("graphs1.txt");
    createGraphs(graphFile);

    // Do the BST stuff
    StringArr* magicItems = readFile("magicitems.txt");

    // Create the binary search tree
    BinarySearchTree bst;

    for (int i = 0; i < magicItems->length; i++) {
        // Add each item to the binary search tree
        BinaryTreeNode<std::string>* newNode = new BinaryTreeNode<std::string>(magicItems->arr[i]);
        bst.insert(newNode);
    }

    // Should be printing in order if the bst inserted everything correctly
    bst.inOrderTraversal();

    StringArr* searchItems = readFile("magicitems-find-in-bst.txt");

    // // Total comparisons starts at 0
    int totalComparisons = 0;

    for (int i = 0; i < searchItems->length; i++) {
        int comparisons = 0;
        // Search the bst for the item
        std::cout << searchItems->arr[i] << " - ";
        bool found = bst.search(searchItems->arr[i], &comparisons);
        std::cout << " - comparisons: " << comparisons << " - found: " << found << std::endl;

        // Add to the total comparisons
        totalComparisons += comparisons;
    }

    // Compute the average and print it out
    double averageComparisons = (double) totalComparisons / searchItems->length;
    std::cout << "Average comparisons: " << averageComparisons << std::endl;

    std::cout << std::endl;

    // Edge case for an element that doesn't exist in the bst
    std::cout << "Nonexistent value: " << bst.search("Test") << std::endl;

    std::cout << std::endl;

    // Make sure comparisons is about 333 for a sorted list before making the tree
    mergeSort(magicItems);

    // Create the binary search tree (should always be on the right, which will be proven with the comparisons for searching)
    BinarySearchTree bstBad;
    for (int i = 0; i < magicItems->length; i++) {
        // Add each item to the binary search tree
        BinaryTreeNode<std::string>* newNode = new BinaryTreeNode<std::string>(magicItems->arr[i]);
        bstBad.insert(newNode, false);
    }

    // Reset totalComparisons to 0 for the new use case
    totalComparisons = 0;

    for (int i = 0; i < searchItems->length; i++) {
        int comparisons = 0;
        // Search the bst for the item
        std::cout << searchItems->arr[i] << " - ";
        bool found = bstBad.search(searchItems->arr[i], &comparisons, false);
        std::cout << "comparisons: " << comparisons << " - found: " << found << std::endl;

        // Add to the total comparisons
        totalComparisons += comparisons;
    }

    // Compute the average and print it out
    averageComparisons = (double) totalComparisons / searchItems->length;
    std::cout << "Average comparisons: " << averageComparisons << std::endl;

    delete [] graphFile->arr;
    delete graphFile;

    delete [] searchItems->arr;
    delete searchItems;

    delete [] magicItems->arr;
    delete magicItems;

    return 0;
}