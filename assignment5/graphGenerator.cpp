#include "graphGenerator.h"
#include "util.h"
#include "graph.h"

#include <iostream>

void createGraphs(StringArr* contents) {
    // Initialize to -1 to denote that no graph has been requested yet
    int curBegin = -1;

    // Go through the file
    for (int i = 0; i < contents->length; i++) {
        // "new graph" marks the end of the past graph
        if (contents->arr[i].compare("new graph") == 0) {
            // Only create the graph if there is a previous graph that has been found
            if (curBegin != -1) {
                std::cout << "New graph" << std::endl;
                try {
                    // Mark the graph from "new graph" to the line before the next "new graph"
                    Graph g(contents, curBegin, i - 1);
                    std::cout << g.bellmanFordSssp() << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                std::cout << std::endl;
            }
            // Set the beginning of the new graph to be the current position
            curBegin = i;
        } else if (i == contents->length - 1) { // EOF also notes the end of a graph
            std::cout << "New graph" << std::endl;
            try {
                // The graph is defined in the rest of the file
                Graph g(contents, curBegin, i);
                std::cout << g.bellmanFordSssp() << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
}