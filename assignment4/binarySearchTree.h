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
        void insert(BinaryTreeNode<std::string>* newNode);

        // Getter for the root
        BinaryTreeNode<std::string>* getRoot();

        // Setter for the root
        void setRoot(BinaryTreeNode<std::string>* newRoot);

    private:
        // The root of the tree
        BinaryTreeNode<std::string>* root;

        // Adds every node in the tree to the queue
        void depthFirstAddToQueue(BinaryTreeNode<std::string>* cur, Queue<BinaryTreeNode<std::string>*>* queue);
};