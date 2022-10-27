#include <string>

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

// Define acceptable data types that the Node can accept for the template
template class BinaryTreeNode<std::string>;