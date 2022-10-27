#pragma once

#include "binaryTreeNode.h"

template <typename T>
class BinarySearchTree {
    public:
        // Constructor
        BinarySearchTree();

        // Inserts the node in the binary search tree
        void insert(BinaryTreeNode<T>* newNode);

        // Getter for the root
        BinaryTreeNode<T>* getRoot();

        // Setter for the root
        void setRoot(BinaryTreeNode<T>* newRoot);

    private:
        BinaryTreeNode<T>* root;
};