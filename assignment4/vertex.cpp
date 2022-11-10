#include "vertex.h"
#include "node.h"
#include "queue.h"

#include <iostream>
      
Vertex::Vertex(int nodeId, int nodeIndex) {
    // Assign the id and index for the graph node
    id = nodeId;
    index = nodeIndex;
    neighbors = new Queue<Vertex*>;

    // Initialize to false because it wasn't worked with yet
    isProcessed = false;

    // std::cout << "Created vertex. Id: " << id << "; Index: " << index << std::endl;
}

Vertex::~Vertex() {
    delete neighbors;
}

void Vertex::addNeighbor(Vertex* newNeighbor) {
    // Create a new node and add it to the front of the list for O(1) time
    Node<Vertex*>* neighborNode = new Node<Vertex*>(newNeighbor);
    neighbors->enqueue(neighborNode);
}

int Vertex::getId() {
    return id;
}

int Vertex::getIndex() {
    return index;
}

Queue<Vertex*>* Vertex::getNeighbors() {
    return neighbors;
}