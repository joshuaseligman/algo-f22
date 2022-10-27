#include "binaryTree.h"
#include "binaryTreeNode.h"

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