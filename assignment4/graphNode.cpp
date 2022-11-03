#include "graphNode.h"
      
GraphNode::GraphNode(int nodeId, int nodeIndex) {
    // Assign the id and index for the graph node
    id = nodeId;
    index = nodeIndex;
}

int GraphNode::getId() {
    return id;
}

int GraphNode::getIndex() {
    return index;
}