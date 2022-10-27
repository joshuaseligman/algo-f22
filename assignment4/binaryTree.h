#pragma once

#include "binaryTreeNode.h"

template <typename T>
class BinaryTree {
    public:
        // Constructor
        BinaryTree();

        // Getter for the root
        BinaryTreeNode<T>* getRoot();

        // Setter for the root
        void setRoot(BinaryTreeNode<T>* newRoot);

    private:
        BinaryTreeNode<T>* root;
};