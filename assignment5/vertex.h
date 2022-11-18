#pragma once

#include "queue.h"
#include "vertex.h"
#include <string>

struct EdgeStruct;

class Vertex {
    public:
        // Constructor for the graph node
        Vertex(std::string nodeId);

        // Destructor for the graph node
        ~Vertex();

        // Adds a new neighbor to the list
        void addNeighbor(Vertex* newNeighbor, int weight);

        // Getter for the id
        std::string getId();

        // Getter for the neighbors queue
        Queue<EdgeStruct*>* getNeighbors();

    private:
        // Id of the vertex
        std::string id;

        // A queue containing the neighboring vertices
        Queue<EdgeStruct*>* neighbors;
};

// The struct to define an edge
struct EdgeStruct {
    // The vertex the edge points to
    Vertex* neighbor;

    // The weight of the edge
    int weight;
};