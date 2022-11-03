#pragma once

class GraphNode {
    public:
        // Constructor for the graph node
        GraphNode(int nodeId, int nodeIndex);

        // Getter for the id
        int getId();

        // Getter for the index the vertex is stored in
        int getIndex();
    private:
        // Id of the vertex
        int id;

        // Index of the vertex in the array in case the first id given is different from 0
        int index;
};