#include "graph.h"

#include "util.h"

#include <iostream>

Graph::Graph(StringArr* data, int beginIndex, int endIndex) {
    numVertices = 0;

    for (int i = beginIndex; i < endIndex; i++) {
        // Get the first 5 characters. Should be "add v" or "add e"
        std::string prefix = data->arr[i].substr(0, 5);

        if (prefix.compare("add v") == 0) {
            numVertices++;
        }
    }

    std::cout << numVertices << std::endl;

    // Create a matrix of size numVertices x numVertices
    matrix = new bool[numVertices * numVertices];

    // Initialize the matrix to be all false
    for (int i = 0; i < numVertices * numVertices; i++) {
        matrix[i] = false;
    }
}

Graph::~Graph() {
    delete [] matrix;
}

void Graph::printMatrix() {
    // Iterate through each row
    for (int i = 0; i < numVertices; i++) {
        // Iterate through each column
        for (int j = 0; j < numVertices; j++) {
            // Print out the value at the given location
            std::cout << matrix[i * numVertices + j] << " ";
        }
        std::cout << std::endl;
    }
}