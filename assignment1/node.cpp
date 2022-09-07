#include <string>

#include "node.h"

Node::Node(std::string initialData) {
    // Initialize the node with the data and without a next node in the linked list
    Node::data = initialData;
    Node::next = nullptr;
}