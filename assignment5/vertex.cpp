#include "vertex.h"
#include "node.h"
#include "queue.h"

#include <iostream>
#include <string>
      
Vertex::Vertex(std::string nodeId) {
    // Assign the id and index for the graph node
    id = nodeId;
    neighbors = new Queue<EdgeStruct*>;

    // std::cout << "Created vertex. Id: " << id << "; Index: " << index << std::endl;
}

Vertex::~Vertex() {
    // Clear the memory being used
    while (!neighbors->isEmpty()) {
        Node<EdgeStruct*>* nodeToDelete = neighbors->dequeue();
        delete nodeToDelete->data;
        delete nodeToDelete;
    }
    delete neighbors;
}

void Vertex::addNeighbor(Vertex* newNeighbor, int weight) {
    // Create the struct to represent the edge pointing to the neighbor
    EdgeStruct* edgeInfo = new EdgeStruct;
    edgeInfo->neighbor = newNeighbor;
    edgeInfo->weight = weight;

    // Create the node and add it to the queue
    Node<EdgeStruct*>* neighborNode = new Node<EdgeStruct*>(edgeInfo);
    neighbors->enqueue(neighborNode);
}

std::string Vertex::getId() {
    return id;
}

Queue<EdgeStruct*>* Vertex::getNeighbors() {
    return neighbors;
}