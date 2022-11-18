#pragma once

#include "node.h"
#include "vertex.h"
#include "util.h"
#include "queue.h"
#include <string>

// Struct for storing data in an adjacency list
struct AdjacencyListStruct {
    std::string vertexId;
    Vertex* vertex;
};

class Graph {
    public:
        // Constructor for a a graph that takes in the range of where to find the graph info in the data (endIndex is inclusive in the range)
        Graph(StringArr* data, int beginIndex, int endIndex);

        // Destructor for a graph
        ~Graph();

        // Gets the vertex of the given id, nullptr if not found
        Vertex* getVertexById(std::string vertexId);

        // Runs the bellman ford sssp algorithm with the single source as the first vertex in the graph
        bool bellmanFordSssp();

        // Prints out the results from the bellman ford algorithm
        void printBellmanFordResults();

    private:
        // Creates a vertex for the linked objects
        void createVertex(std::string vertexInfo);

        // Creates an edge for the linked objects
        void createEdge(std::string edgeInfo);

        // Initializes the graph for bellman ford
        void initSingleSource(Vertex* source);

        // Makes any needed changes for the shortest path to the given vertex
        void relax(Vertex* vertex, EdgeStruct* edge);

        // The number of vertices in the graph
        int numVertices;

        // Stores a pointer to the head of a linked list containing all the vertices
        Queue<Vertex*>* vertices;
};