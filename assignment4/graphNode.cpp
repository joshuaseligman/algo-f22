#include "graphNode.h"

#include <iostream>
      
GraphNode::GraphNode(int nodeId, int nodeIndex) {
    // Assign the id and index for the graph node
    id = nodeId;
    index = nodeIndex;

    std::cout << "Created vertex. Id: " << id << "; Index: " << index << std::endl;
}

int GraphNode::getId() {
    return id;
}

int GraphNode::getIndex() {
    return index;
}