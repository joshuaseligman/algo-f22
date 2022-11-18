#include "graph.h"

#include "util.h"
#include "node.h"
#include "vertex.h"
#include "queue.h"

#include <regex>
#include <iostream>
#include <sstream>

Graph::Graph(StringArr* data, int beginIndex, int endIndex) {
    numVertices = 0;
    vertices = new Queue<Vertex*>;

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

    // std::cout << numVertices << std::endl;
}

Graph::~Graph() {
    delete vertices;
}

void Graph::createVertex(std::string vertexInfo) {
    char* ptr;
    ptr = strtok(vertexInfo.data(), " ");

    bool idNext = false;
    std::string vertexId;

    while (ptr != NULL) {
        std::stringstream ss(ptr);
        if (idNext) {
            // Get the id and break
            vertexId = ss.str();

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
    Vertex* newVertex = new Vertex(vertexId);

    // Create the regular node and store it in the list at the front to keep O(1) time
    Node<Vertex*>* newNode = new Node<Vertex*>(newVertex);
    vertices->enqueue(newNode);

    // Increment the number of vertices
    numVertices++;
}

void Graph::createEdge(std::string edgeInfo) {
    // Variable to store the match results
    std::smatch m;
    // Regular expression looks for a number followed by a space, hyphen, space, and another number
    std::regex e("\\w+ - \\w+");

    // Try to find the match
    std::regex_search(edgeInfo, m, e);

    bool firstId = true;

    std::string id1 = "";
    std::string id2 = "";

    char* ptr;
    // Only work with the substring that is the vertices
    ptr = strtok(edgeInfo.substr(m.position(), m.length()).data(), " - ");
    while (ptr != NULL) {
        std::stringstream ss(ptr);
        if (firstId) {
            // Store the id of the first vertex
            id1 = ss.str();
            firstId = false;
        } else {
            // Store the id of the second vertex
            id2 = ss.str();
        }
        ptr = strtok(NULL, " - ");
    }

    Vertex* v1 = getVertexById(id1);
    if (v1 == nullptr) {
        // Create an error message if the vertex was not found
        std::stringstream ss;
        ss << "Vertex " << id1 << " does not exist";
        throw std::invalid_argument(ss.str());
    }

    Vertex* v2 = getVertexById(id2);
    if (v2 == nullptr) {
        // Create an error message if the vertex was not found
        std::stringstream ss;
        ss << "Vertex " << id2 << " does not exist";
        throw std::invalid_argument(ss.str());
    }

    // Not supporting multigraphs
    Node<Vertex*>* cur = v1->getNeighbors()->getHead();
    while (cur != nullptr) {
        if (cur->data->getId() == v2->getId()) {
            // Throw error if the edge already exists
            std::stringstream ss;
            ss << "Edge " << v1->getId() << " - " << v2->getId() << " already exists";
            throw std::invalid_argument(ss.str());
        }
        cur = cur->next;
    }

    // Add each vertex to the neighbors list
    v1->addNeighbor(v2);
    v2->addNeighbor(v1);

    // std::cout << "Created edge " << v1->getId() << " - " << v2->getId() << std::endl;
}

Vertex* Graph::getVertexById(std::string vertexId) {
    // Start at the head of the list
    Node<Vertex*>* cur = vertices->getHead();

    // Assume not found
    bool found = false;

    while (cur != nullptr && !found) {
        // Set found to true if the id matches
        if (cur->data->getId().compare(vertexId) == 0) {
            found = true;
        } else {
            // Otherwise move on to the next vertex
            cur = cur->next;
        }
    }

    // Return the vertex
    Vertex* out = nullptr;
    if (cur != nullptr) {
        out = cur->data;
    }
    return out;
}