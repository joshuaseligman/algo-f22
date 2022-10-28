#include "binarySearchTree.h"
#include "binaryTreeNode.h"
#include "queue.h"

#include <string>
#include <iostream>

BinarySearchTree::BinarySearchTree() {
    // Initialize the root to be a null pointer
    BinarySearchTree::root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    // Create a queue for things to delete
    Queue<BinaryTreeNode<std::string>*> removalQueue;

    // Add all nodes to the queue, starting with the root
    depthFirstAddToQueue(root, &removalQueue);

    // Continue for all nodes
    while (!removalQueue.isEmpty()) {
        // Get the next node
        Node<BinaryTreeNode<std::string>*>* nodeToDelete = removalQueue.dequeue();

        // Delete the binary tree node element
        delete nodeToDelete->data;

        // Delete the regular node element from the queue
        delete nodeToDelete;
    }
}

void BinarySearchTree::insert(BinaryTreeNode<std::string>* newNode) {
    // Set the trailing pointer to be null
    BinaryTreeNode<std::string>* trailing = nullptr;

    // Start at the root of the tree
    BinaryTreeNode<std::string>* cur = root;

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

bool BinarySearchTree::search(std::string target, int* comparisons) {
    // Run the search starting with the root of the tree
    return searchHelper(target, root, comparisons);
}

bool BinarySearchTree::searchHelper(std::string target, BinaryTreeNode<std::string>* cur, int* comparisons) {
    // Assume the element is not found (cur is nullptr)
    bool out = false;

    if (cur != nullptr) {
        // Compare the strings
        int strComp = target.compare(cur->data);

        // A comparison was made, so increment the counter
        if (comparisons != nullptr) {
            (*comparisons)++;
        }

        if (strComp ==  0) {
            // The element was found, so return true
            out = true;
        } else if (strComp < 0) {
            // Check the left side because the target is less than the current value
            std::cout << "L";
            out = searchHelper(target, cur->left, comparisons);
        } else {
            // Check the right side because the target is greater than the current value
            std::cout << "R";
            out = searchHelper(target, cur->right, comparisons);
        }
    }

    return out;
}

void BinarySearchTree::depthFirstAddToQueue(BinaryTreeNode<std::string>* cur, Queue<BinaryTreeNode<std::string>*>* queue) {
    if (cur != nullptr) {
        // Add the current node to the queue
        Node<BinaryTreeNode<std::string>*>* curNode = new Node<BinaryTreeNode<std::string>*>(cur);
        queue->enqueue(curNode);

        // Check to add the left and right child nodes to the queue
        depthFirstAddToQueue(cur->left, queue);
        depthFirstAddToQueue(cur->right, queue);
    }
}

void BinarySearchTree::inOrderTraversal() {
    // Perform the in order traversal starting with the root
    BinaryTreeNode<std::string>::inOrderTraversal(root);
}

BinaryTreeNode<std::string>* BinarySearchTree::getRoot() {
    return root;
}

void BinarySearchTree::setRoot(BinaryTreeNode<std::string>* newRoot) {
    root = newRoot;
}