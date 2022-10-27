#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"
#include "binarySearchTree.h"
#include "binaryTreeNode.h"

int main() {
    StringArr* magicItems = readFile("magicitems.txt");

    BinarySearchTree bst;

    for (int i = 0; i < magicItems->length; i++) {
       BinaryTreeNode<std::string>* newNode = new BinaryTreeNode<std::string>(magicItems->arr[i]);
       bst.insert(newNode);
    }

    StringArr* searchItems = readFile("magicitems-find-in-bst.txt");

    int totalComparisons = 0;
    for (int i = 0; i < searchItems->length; i++) {
        int comparisons = 0;
        bool found = bst.search(searchItems->arr[i], &comparisons);
        std::cout << " - " << comparisons << " - " << found << std::endl;

        totalComparisons += comparisons;
    }

    double averageComparisons = (double) totalComparisons / searchItems->length;
    std::cout << "Average comparisons: " << averageComparisons << std::endl;

    std::cout << bst.search("Test") << std::endl;

    delete [] searchItems->arr;
    delete searchItems;

    delete [] magicItems->arr;
    delete magicItems;

    return 0;
}