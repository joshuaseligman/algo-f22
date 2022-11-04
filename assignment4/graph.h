#pragma once

#include "node.h"
#include "graphNode.h"
#include "util.h"
#include "queue.h"

// Struct for storing data in an adjacency list
struct AdjacencyListStruct {
    int vertexId;
    GraphNode* vertex;
};

class Graph {
    public:
        // Constructor for a a graph that takes in the range of where to find the graph info in the data (endIndex is inclusive in the range)
        Graph(StringArr* data, int beginIndex, int endIndex);

        // Destructor for a graph
        ~Graph();

        // Function to print out the matrix
        void printMatrix();

        // Function to print out the adjacency list
        void printAdjacencyList();

        // Performs a depth first search on the entire graph and prints out the vertex ids of the encountered vertices
        void depthFirstSearch();

        // Helper function that does the dfs from the given node
        void depthFirstSearchHelper(GraphNode* start);

        // Resets all vertices to be not processed
        void clearProcessedStates();

        // Gets the graph node of the given id, nullptr if not found
        GraphNode* getGraphNode(int nodeId);

    private:
        // Creates a vertex for the linked objects
        void createVertex(std::string vertexInfo);

        // Creates an edge for the linked objects
        void createEdge(std::string edgeInfo);

        // Creates the matrix representation of the graph based on the nodes already created
        void createMatrix();

        // Creates the adjacency list representation of the graph based on the nodes already created
        void createAdjacencyList();

        // The number of vertices in the graph
        int numVertices;

        // Stores a pointer to the head of a linked list containing all the vertices
        Queue<GraphNode*>* vertices;

        // The matrix representation of the graph
        bool* matrix;

        // Adjacency list is an array of queues for the neighboring vertices
        Queue<AdjacencyListStruct*>* adjacencyList;
};