#pragma once

#include "queue.h"

class GraphNode {
    public:
        // Constructor for the graph node
        GraphNode(int nodeId, int nodeIndex);

        // Destructor for the graph node
        ~GraphNode();

        // Adds a new neighbor to the list
        void addNeighbor(GraphNode* newNeighbor);

        // Getter for the id
        int getId();

        // Getter for the index the vertex is stored in
        int getIndex();

        // Getter for the neighbors queue
        Queue<GraphNode*>* getNeighbors();
    private:
        // Id of the vertex
        int id;

        // Index of the vertex in the array in case the first id given is different from 0
        int index;

        // A queue containing the neighboring vertices
        Queue<GraphNode*>* neighbors;
};