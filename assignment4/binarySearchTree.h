#pragma once

#include <string>
#include "binaryTreeNode.h"
#include "queue.h"

class BinarySearchTree {
    public:
        // Constructor
        BinarySearchTree();

        ~BinarySearchTree();

        // Inserts the node in the binary search tree
        void insert(BinaryTreeNode<std::string>* newNode, bool shouldPrintPath = true);

        // Searches for a value in the binary search tree
        bool search(std::string target, int* comparisons = nullptr, bool shouldPrintPath = true);

        // Helper function for searching for an element in the binary search tree
        bool searchHelper(std::string target, BinaryTreeNode<std::string>* cur, int* comparisons, bool shouldPrintPath);

        // Traverse the tree from the root of the node
        void inOrderTraversal();

        // Getter for the root
        BinaryTreeNode<std::string>* getRoot();

        // Setter for the root
        void setRoot(BinaryTreeNode<std::string>* newRoot);

    private:
        // The root of the tree
        BinaryTreeNode<std::string>* root;

        // Adds every node in the tree to the queue
        void preOrderAddToQueue(BinaryTreeNode<std::string>* cur, Queue<BinaryTreeNode<std::string>*>* queue);
};