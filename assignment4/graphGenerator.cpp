#include "graphGenerator.h"
#include "util.h"

#include <iostream>

void createGraphs(StringArr* contents) {
    for (int i = 0; i < contents->length; i++) {
        std::cout << contents->arr[i] << std::endl;
    }
}