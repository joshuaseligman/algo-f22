#include <string>
#include <iostream>

#include "binaryTreeNode.h"

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(T initialData) {
    // Initialize the node with the data and without left, right, or parent nodes in the tree
    BinaryTreeNode::data = initialData;

    BinaryTreeNode::left = nullptr;
    BinaryTreeNode::right = nullptr;
    BinaryTreeNode::parent = nullptr;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode() {
    // Initialize the node to not have a left, right, or parent nodes
    BinaryTreeNode::left = nullptr;
    BinaryTreeNode::right = nullptr;
    BinaryTreeNode::parent = nullptr;
}

template <typename T>
void BinaryTreeNode<T>::inOrderTraversal(BinaryTreeNode<T>* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << node->data << std::endl;
        inOrderTraversal(node->right);
    }
}

// Define acceptable data types that the Node can accept for the template
template class BinaryTreeNode<std::string>;