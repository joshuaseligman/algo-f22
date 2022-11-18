#pragma once

#include "queue.h"
#include "vertex.h"
#include <string>

class Vertex {
    public:
        // Constructor for the graph node
        Vertex(std::string nodeId, int nodeIndex);

        // Destructor for the graph node
        ~Vertex();

        // Adds a new neighbor to the list
        void addNeighbor(Vertex* newNeighbor);

        // Getter for the id
        std::string getId();

        // Getter for the index the vertex is stored in
        int getIndex();

        // Getter for the neighbors queue
        Queue<Vertex*>* getNeighbors();

        // Boolean to determine if the node was processed during a traversal
        bool isProcessed;
    private:
        // Id of the vertex
        std::string id;

        // Index of the vertex in the array in case the first id given is different from 0
        int index;

        // A queue containing the neighboring vertices
        Queue<Vertex*>* neighbors;
};