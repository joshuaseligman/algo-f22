#pragma once

#include "node.h"

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

        // Getter for the neighbors linked list
        Node<GraphNode*>* getNeighbors();
    private:
        // Id of the vertex
        int id;

        // Index of the vertex in the array in case the first id given is different from 0
        int index;

        // A linked list containing the neighboring vertices
        Node<GraphNode*>* neighbors;
};