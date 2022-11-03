#include "graphNode.h"
#include "node.h"

#include <iostream>
      
GraphNode::GraphNode(int nodeId, int nodeIndex) {
    // Assign the id and index for the graph node
    id = nodeId;
    index = nodeIndex;
    neighbors = nullptr;

    std::cout << "Created vertex. Id: " << id << "; Index: " << index << std::endl;
}

GraphNode::~GraphNode() {
    Node<GraphNode*>* cur = neighbors;

    // Delete all nodes
    while (cur != nullptr) {
        Node<GraphNode*>* toBeDeleted = cur;
        cur = cur->next;

        // Only delete the node, the actual data will be deleted in the Graph destructor
        delete toBeDeleted;
    }
}

void GraphNode::addNeighbor(GraphNode* newNeighbor) {
    // Create a new node and add it to the front of the list for O(1) time
    Node<GraphNode*>* neighborNode = new Node<GraphNode*>(newNeighbor);
    neighborNode->next = neighbors;
    neighbors = neighborNode;
}

int GraphNode::getId() {
    return id;
}

int GraphNode::getIndex() {
    return index;
}

Node<GraphNode*>* GraphNode::getNeighbors() {
    return neighbors;
}