#pragma once

#include "queue.h"
#include "vertex.h"
#include <string>

class Vertex {
    public:
        // Constructor for the graph node
        Vertex(std::string nodeId);

        // Destructor for the graph node
        ~Vertex();

        // Adds a new neighbor to the list
        void addNeighbor(Vertex* newNeighbor);

        // Getter for the id
        std::string getId();

        // Getter for the neighbors queue
        Queue<Vertex*>* getNeighbors();

    private:
        // Id of the vertex
        std::string id;

        // A queue containing the neighboring vertices
        Queue<Vertex*>* neighbors;
};