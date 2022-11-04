#include "graph.h"

#include "util.h"
#include "node.h"
#include "graphNode.h"
#include "queue.h"

#include <regex>
#include <iostream>
#include <sstream>

Graph::Graph(StringArr* data, int beginIndex, int endIndex) {
    numVertices = 0;
    vertices = new Queue<GraphNode*>;

    for (int i = beginIndex; i <= endIndex; i++) {
        // Get the first 5 characters. Should be "add v" or "add e"
        std::string prefix = data->arr[i].substr(0, 5);

        if (prefix.compare("add v") == 0) {
            // Create a vertex
            createVertex(data->arr[i]);
        } else if (prefix.compare("add e") == 0) {
            // Add the edge
            createEdge(data->arr[i]);
        }
    }

    std::cout << numVertices << std::endl;

    createMatrix();

    createAdjacencyList();
}

Graph::~Graph() {
    delete [] matrix;
    delete vertices;
    delete [] adjacencyList;
}

void Graph::createVertex(std::string vertexInfo) {
    char* ptr;
    ptr = strtok(vertexInfo.data(), " ");

    bool idNext = false;
    int vertexId;

    while (ptr != NULL) {
        std::stringstream ss(ptr);
        if (idNext) {
            // Get the id and break
            ss >> vertexId;

            // Change back to false and let the strtok function break the loop
            idNext = false;
        } else if (ss.str().compare("vertex") == 0) {
            // We know the next segment is going to be the id of the vertex
            idNext = true;
        }

        // Check the next word
        ptr = strtok(NULL, " ");
    }

    // Create the graph node
    GraphNode* newGraphNode = new GraphNode(vertexId, numVertices);

    // Create the regular node and store it in the list at the front to keep O(1) time
    Node<GraphNode*>* newNode = new Node<GraphNode*>(newGraphNode);
    vertices->enqueue(newNode);

    // Increment the number of vertices
    numVertices++;
}

void Graph::createEdge(std::string edgeInfo) {
    // Variable to store the match results
    std::smatch m;
    // Regular expression looks for a number followed by a space, hyphen, space, and another number
    std::regex e("\\d+ - \\d+");

    // Try to find the match
    std::regex_search(edgeInfo, m, e);

    bool firstId = true;

    int id1 = INT_MIN;
    int id2 = INT_MIN;

    char* ptr;
    // Only work with the substring that is the vertices
    ptr = strtok(edgeInfo.substr(m.position(), m.length()).data(), " - ");
    while (ptr != NULL) {
        std::stringstream ss(ptr);
        if (firstId) {
            // Store the id of the first vertex
            ss >> id1;
            firstId = false;
        } else {
            // Store the id of the second vertex
            ss >> id2;
        }
        ptr = strtok(NULL, " - ");
    }

    GraphNode* v1 = getGraphNode(id1);
    if (v1 == nullptr) {
        // Create an error message if the vertex was not found
        std::stringstream ss;
        ss << "Vertex " << id1 << " does not exist";
        throw std::invalid_argument(ss.str());
    }

    GraphNode* v2 = getGraphNode(id2);
    if (v2 == nullptr) {
        // Create an error message if the vertex was not found
        std::stringstream ss;
        ss << "Vertex " << id2 << " does not exist";
        throw std::invalid_argument(ss.str());
    }

    // Add each vertex to the neighbors list
    v1->addNeighbor(v2);
    v2->addNeighbor(v1);

    std::cout << "Created edge " << v1->getId() << " - " << v2->getId() << std::endl;
}

void Graph::createMatrix() {
    // Create a matrix of size numVertices x numVertices
    matrix = new bool[numVertices * numVertices];

    // Initialize the matrix to be all false
    for (int i = 0; i < numVertices * numVertices; i++) {
        matrix[i] = false;
    }

    // Go through all vertices
    Node<GraphNode*>* cur = vertices->getHead();
    while (cur != nullptr) {
        // Go through all of the neighbors
        Node<GraphNode*>* neighbor = cur->data->getNeighbors()->getHead();
        while (neighbor != nullptr) {
            matrix[cur->data->getIndex() * numVertices + neighbor->data->getIndex()] = true;
            neighbor = neighbor->next;
        }
        cur = cur->next;
    }
}

void Graph::createAdjacencyList() {
    // Each vertex will have its own adjacency list
    adjacencyList = new Queue<AdjacencyListStruct*>[numVertices];

    // Go through all vertices
    Node<GraphNode*>* cur = vertices->getHead();
    while (cur != nullptr) {
        // Go through all of its neighbors
        Node<GraphNode*>* neighbor = cur->data->getNeighbors()->getHead();
        while (neighbor != nullptr) {
            // Create the data and store it
            AdjacencyListStruct* newData = new AdjacencyListStruct;
            newData->vertexId = neighbor->data->getId();
            newData->vertex = neighbor->data;

            Node<AdjacencyListStruct*>* newNode = new Node<AdjacencyListStruct*>(newData);

            // Add the struct to the end of the queue
            adjacencyList[cur->data->getIndex()].enqueue(newNode);

            neighbor = neighbor->next;
        }

        cur = cur->next;
    }
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

void Graph::printAdjacencyList() {
    // Go through each vertex
    Node<GraphNode*>* cur = vertices->getHead();
    while (cur != nullptr) {
        // Print out the vertex's id
        std::cout << cur->data->getId() << ": ";

        // Go through all of the neighbors
        Node<AdjacencyListStruct*>* neighbor = adjacencyList[cur->data->getIndex()].getHead();

        while (neighbor != nullptr) {
            // Print out the neighbor id
            std::cout << neighbor->data->vertexId << " ";
            neighbor = neighbor->next;
        }

        std::cout << std::endl;

        cur = cur->next;
    }
}

void Graph::depthFirstSearch() {
    // Make sure everything is cleared
    clearProcessedStates();

    Node<GraphNode*>* start = vertices->getHead();

    while (start != nullptr) {
        // If the vertex has not been processed, it is disconnected from the rest of the graph
        if (!start->data->isProcessed) {
            // Start the DFS from the current node to explore that region of the graph
            std::cout << "DFS: ";
            depthFirstSearch(start->data);
            std::cout << std::endl;
        }
        start = start->next;
    }
}

void Graph::depthFirstSearch(GraphNode* start) {
    if (!start->isProcessed) {
        // Print out the vertex id only if it hasn't been processed yet
        std::cout << start->getId() << " ";
        start->isProcessed = true;
    }
    // Iterate through all neighbors
    Node<GraphNode*>* cur = start->getNeighbors()->getHead();
    while (cur != nullptr) {
        if (!cur->data->isProcessed) {
            // Run a DFS starting from the neighbor if it hasn't been processed already
            depthFirstSearch(cur->data);
        }
        cur = cur->next;
    }
}

void Graph::breadthFirstSearch() {
    // Reset the processed states
    clearProcessedStates();

    Node<GraphNode*>* start = vertices->getHead();

    while (start != nullptr) {
        // If the vertex has not been processed, it is disconnected from the rest of the graph
        if (!start->data->isProcessed) {
            // Start the BFS from the current node to explore that region of the graph
            std::cout << "BFS: ";
            // Do a breadth first search from the first vertex
            breadthFirstSearch(start->data);
            std::cout << std::endl;
        }
        start = start->next;
    }
}

void Graph::breadthFirstSearch(GraphNode* start) {
    // Create the queue for the vertices to check
    Queue<GraphNode*> verticesToCheck;

    // Add the start to the queue
    Node<GraphNode*>* startNode = new Node<GraphNode*>(start);
    verticesToCheck.enqueue(startNode);
    startNode->data->isProcessed = true;

    // Continue until no more vertices are left to check
    while (!verticesToCheck.isEmpty()) {
        // Get the next vertex and print it out
        Node<GraphNode*>* check = verticesToCheck.dequeue();
        std::cout << check->data->getId() << " ";

        Node<GraphNode*>* cur = check->data->getNeighbors()->getHead();
        while (cur != nullptr) {
            if (!cur->data->isProcessed) {
                // Create a new node and add it to the queue
                Node<GraphNode*>* newNode = new Node<GraphNode*>(cur->data);
                verticesToCheck.enqueue(newNode);
                newNode->data->isProcessed = true;
            }
            cur = cur->next;
        }

        delete check;
    }
}

void Graph::clearProcessedStates() {
    // Initialize all nodes to not be processed yet
    Node<GraphNode*>* cur = vertices->getHead();
    while (cur != nullptr) {
        cur->data->isProcessed = false;
        cur = cur->next;
    }
}

GraphNode* Graph::getGraphNode(int nodeId) {
    // Start at the head of the list
    Node<GraphNode*>* cur = vertices->getHead();

    // Assume not found
    bool found = false;

    while (cur != nullptr && !found) {
        // Set found to true if the id matches
        if (cur->data->getId() == nodeId) {
            found = true;
        } else {
            // Otherwise move on to the next node
            cur = cur->next;
        }
    }

    // Return the graph node
    return cur->data;
}