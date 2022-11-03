#include "graphGenerator.h"
#include "util.h"

#include <iostream>

void createGraphs(StringArr* contents) {
    for (int i = 0; i < contents->length; i++) {
        // Get the first 3 letters of the line
        std::string prefix = contents->arr[i].substr(0, 3);
        // Only do something if the first 3 letters are "add" or "new"
        if (prefix.compare("add") != 0 && prefix.compare("new") != 0) {
            // Go to the next line
            continue;
        }
        std::cout << contents->arr[i] << std::endl;
    }
}