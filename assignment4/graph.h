#pragma once

#include "util.h"

class Graph {
    public:
        // Constructor for a a graph that takes in the range of where to find the graph info in the data (endIndex is inclusive in the range)
        Graph(StringArr* data, int beginIndex, int endIndex);

        // Destructor for a graph
        ~Graph();

    private:
        // The number of vertices in the graph
        int numVertices;

        // The matrix representation of the graph
        bool* matrix;
};