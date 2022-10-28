#pragma once

// Node represents an item within a singly linked list and can store data of a given type
template <typename T>
class BinaryTreeNode {
    public:
        // A node has the data it is storing (of a type defined by the user) and a pointer to the next node
        T data;

        // The left branch node
        BinaryTreeNode<T>* left;

        // The right branch node
        BinaryTreeNode<T>* right;

        // The parent node (null means root)
        BinaryTreeNode<T>* parent;

        // Nodes will be instantiated with some data and not have a next node
        BinaryTreeNode(T initialData);

        // Implicit constructor
        BinaryTreeNode();

        // Traverse through a binary tree starting with the node
        static void inOrderTraversal(BinaryTreeNode<T>* node);
};

// Super helpful resource on templates for c++
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl