#include <iostream>
#include <sstream>

#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"
#include "resident.h"

int main() {
    StringArr* data = readFile("testData1.txt");

    // String split code from: https://www.javatpoint.com/how-to-split-strings-in-cpp
    // A pointer to each part of the split string
    char* ptr;
    // Get the first token
    ptr = strtok(data->arr[0].data(), " ");

    int numResidents = -1;
    int numHospitals = -1;

    // Continue until the end of the string  
    while (ptr != NULL) {
        // String to integer conversion https://www.geeksforgeeks.org/converting-strings-numbers-c-cpp/
        std::stringstream ss(ptr);
        if (numResidents == -1) {
            ss >> numResidents;
        } else {
            ss >> numHospitals;
        }
        ptr = strtok(NULL, " ");  
    }

    std::cout << numResidents << " " << numHospitals << std::endl;

    // Memory management and clean up
    // delete [] residents->arr;
    // delete residents;

    // delete [] hospitals->arr;
    // delete hospitals;

    delete [] data->arr;
    delete data;
}