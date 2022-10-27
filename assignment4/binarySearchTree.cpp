#include "binarySearchTree.h"
#include "binaryTreeNode.h"

#include <string>
#include <iostream>

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
    // Initialize the root to be a null pointer
    BinarySearchTree::root = nullptr;
}

template <typename T>
void BinarySearchTree<T>::insert(BinaryTreeNode<T>* newNode) {
    // Set the trailing pointer to be null
    BinaryTreeNode<T>* trailing = nullptr;

    // Start at the root of the tree
    BinaryTreeNode<T>* cur = root;

    // Continue until we are at the leaf node to insert the new node
    while (cur != nullptr) {
        // Update the trailing pointer
        trailing = cur;
        if (newNode->data.compare(cur->data) < 0) {
            // Smaller items go to the left
            cur = cur->left;
            std::cout << "L";
        } else {
            // Larger or equal items go to the right
            cur = cur->right;
            std::cout << "R";
        }
    }
    std::cout << std::endl;

    // Trailing is one level above the node and is the parent
    newNode->parent = trailing;

    if (trailing == nullptr) {
        // Set the root to be the new node if the trailing pointer is null
        // The while loop was never entered
        root = newNode;
    } else {
        if (newNode->data.compare(trailing->data) < 0) {
            // The new node is on the left of its parent
            trailing->left = newNode;
        } else {
            // The new node is on the right of its parent
            trailing->right = newNode;
        }
    }
}

template <typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::getRoot() {
    return root;
}

template <typename T>
void BinarySearchTree<T>::setRoot(BinaryTreeNode<T>* newRoot) {
    root = newRoot;
}

// Define acceptable data types that the binary search tree can accept for the template
template class BinarySearchTree<std::string>;