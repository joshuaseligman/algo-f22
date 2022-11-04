#include "graphNode.h"
#include "node.h"
#include "queue.h"

#include <iostream>
      
GraphNode::GraphNode(int nodeId, int nodeIndex) {
    // Assign the id and index for the graph node
    id = nodeId;
    index = nodeIndex;
    neighbors = new Queue<GraphNode*>;

    std::cout << "Created vertex. Id: " << id << "; Index: " << index << std::endl;
}

GraphNode::~GraphNode() {
    delete neighbors;
}

void GraphNode::addNeighbor(GraphNode* newNeighbor) {
    // Create a new node and add it to the front of the list for O(1) time
    Node<GraphNode*>* neighborNode = new Node<GraphNode*>(newNeighbor);
    neighbors->enqueue(neighborNode);
}

int GraphNode::getId() {
    return id;
}

int GraphNode::getIndex() {
    return index;
}

Queue<GraphNode*>* GraphNode::getNeighbors() {
    return neighbors;
}