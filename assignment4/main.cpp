#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"
#include "binarySearchTree.h"
#include "binaryTreeNode.h"

#include "sortsAndShuffles.h"

int main() {
    StringArr* magicItems = readFile("magicitems.txt");
    // mergeSort(magicItems);

    // Create the binary search tree
    BinarySearchTree bst;

    for (int i = 0; i < magicItems->length; i++) {
        // Add each item to the binary search tree
        BinaryTreeNode<std::string>* newNode = new BinaryTreeNode<std::string>(magicItems->arr[i]);
        bst.insert(newNode);
    }

    bst.inOrderTraversal();

    StringArr* searchItems = readFile("magicitems-find-in-bst.txt");

    // Total comparisons starts at 0
    int totalComparisons = 0;

    for (int i = 0; i < searchItems->length; i++) {
        int comparisons = 0;
        // Search the bst for the item
        bool found = bst.search(searchItems->arr[i], &comparisons);
        std::cout << " - " << comparisons << " - " << found << std::endl;

        // Add to the total comparisons
        totalComparisons += comparisons;
    }

    // Compute the average and print it out
    double averageComparisons = (double) totalComparisons / searchItems->length;
    std::cout << "Average comparisons: " << averageComparisons << std::endl;

    // Edge case for an element that doesn't exist in the bst
    std::cout << bst.search("Test") << std::endl;

    delete [] searchItems->arr;
    delete searchItems;

    delete [] magicItems->arr;
    delete magicItems;

    return 0;
}