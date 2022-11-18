#include "vertex.h"
#include "node.h"
#include "queue.h"

#include <iostream>
#include <string>
      
Vertex::Vertex(std::string nodeId) {
    // Assign the id and index for the graph node
    id = nodeId;
    neighbors = new Queue<Vertex*>;

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

std::string Vertex::getId() {
    return id;
}

Queue<Vertex*>* Vertex::getNeighbors() {
    return neighbors;
}