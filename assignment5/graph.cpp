#include "graph.h"

#include "util.h"
#include "node.h"
#include "vertex.h"
#include "queue.h"
#include "stack.h"

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

    // Get the weight by starting with the character after the indices until the end of the string
    int weight = std::stoi(edgeInfo.substr(m.position() + m.length() + 1, edgeInfo.length()));

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
    Node<EdgeStruct*>* cur = v1->getNeighbors()->getHead();
    while (cur != nullptr) {
        if (cur->data->neighbor->getId().compare(v2->getId()) == 0) {
            // Throw error if the edge already exists
            std::stringstream ss;
            ss << "Edge " << v1->getId() << " - " << v2->getId() << " already exists";
            throw std::invalid_argument(ss.str());
        }
        cur = cur->next;
    }

    // Add each vertex to the neighbors list
    v1->addNeighbor(v2, weight);

    std::cout << "Created edge " << v1->getId() << " - " << v2->getId() << "; weight: " << weight << std::endl;
}

bool Graph::bellmanFordSssp() {
    // Assume no negative weight cycles
    bool out = true;

    // Initialize the vertices based on the source vertex
    initSingleSource(vertices->getHead()->data);

    for (int i = 0; i < numVertices - 1; i++) {
        Node<Vertex*>* cur = vertices->getHead();
        // Iterate through each vertex
        while (cur != nullptr) {
            Node<EdgeStruct*>* edgeNode = cur->data->getNeighbors()->getHead();
            // With the other while loop, this effectively iterates through all of the edges in the graph
            while (edgeNode != nullptr) {
                // See if the edge is a better path for the vertex it points to
                relax(cur->data, edgeNode->data);
                edgeNode = edgeNode->next;
            }
            cur = cur->next;
        }
    }

    Node<Vertex*>* cur = vertices->getHead();
    // Go through each vertex
    while (cur != nullptr && out == true) {
        Node<EdgeStruct*>* edgeNode = cur->data->getNeighbors()->getHead();
        // Iterate through all of the edges in the graph with the nested while loops
        while (edgeNode != nullptr && out == true) {
            // Check for a negative weight cycle
            if (edgeNode->data->neighbor->ssspDistance > cur->data->ssspDistance + edgeNode->data->weight) {
                out = false;
            }
            edgeNode = edgeNode->next;
        }
        cur = cur->next;
    }

    return out;
}

void Graph::initSingleSource(Vertex* source) {
    Node<Vertex*>* cur = vertices->getHead();
    while (cur != nullptr) {
        // Add no predecessor and assume the distance is an arbitrary represetation of infinity
        cur->data->predecessor = nullptr;
        cur->data->ssspDistance = 1000000000;

        cur = cur->next;
    }
    // Override what we did earlier because the path from the source to the source is 0
    source->ssspDistance = 0;
}

void Graph::relax(Vertex* vertex, EdgeStruct* edge) {
    // Check to see if the edge is a better route to the vertex it points to
    if (edge->neighbor->ssspDistance > vertex->ssspDistance + edge->weight) {
        // If so, make the adjustments to the variables
        edge->neighbor->ssspDistance = vertex->ssspDistance + edge->weight;
        edge->neighbor->predecessor = vertex;
    }
}

void Graph::printBellmanFordResults() {
    Node<Vertex*>* cur = vertices->getHead();
    // Print the results for the path to each vertex
    while (cur != nullptr) {
        // Stack to reverse the order of the vertices that are printed
        Stack<std::string> ssspOutput;

        // Start with the current vertex
        Node<std::string>* curIdNode = new Node<std::string>(cur->data->getId());
        ssspOutput.push(curIdNode);

        // Do not forget to keep the cost
        int cost = cur->data->ssspDistance;

        // Go through all the predecessors
        Vertex* predecessorVertex = cur->data->predecessor;
        while (predecessorVertex != nullptr) {
            // Add the id of the predecessor
            Node<std::string>* predecessorId = new Node<std::string>(predecessorVertex->getId());
            ssspOutput.push(predecessorId);

            predecessorVertex = predecessorVertex->predecessor;
        }

        bool first = true;
        // Print out all of the vertices from the stack
        while (!ssspOutput.isEmpty()) {
            // Clean output with the arrow
            if (!first) {
                std::cout << " -> ";
            } else {
                first = false;
            }
            // Print the id of the vertex
            Node<std::string>* outNode = ssspOutput.pop();
            std::cout << outNode->data;

            // Memory management
            delete outNode;
        }
        // Print the overall cost
        std::cout << "; cost = " << cost << std::endl;

        cur = cur->next;
    }
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