#include "binaryTree.h"
#include "binaryTreeNode.h"

#include <string>

template <typename T>
BinaryTree<T>::BinaryTree() {
    // Initialize the root to be a null pointer
    BinaryTree::root = nullptr;
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::getRoot() {
    return root;
}

template <typename T>
void BinaryTree<T>::setRoot(BinaryTreeNode<T>* newRoot) {
    root = newRoot;
}

// Define acceptable data types that the binary tree can accept for the template
template class BinaryTree<std::string>;
template class BinaryTree<char>;