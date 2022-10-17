#include "hospital.h"
#include "resident.h"

#include <string>
#include <sstream>
#include <iostream>

Hospital::Hospital() {
    // Initialize these variables to be nothing
    numAssigned = 0;
}

Hospital::~Hospital() {
    
}

void Hospital::loadData(std::string data, int hospIndex, ResidentArr* residents) {
    // The part of the line before the colon is the name
    int colonIndex = data.find(":");
    name = data.substr(0, colonIndex);

    // Set the index of the element (number in string - 1), but quicker to pass the index as is
    index = hospIndex;

    // Get the remainder of the string after the colon and the space
    std::string remainder = data.substr(colonIndex + 2, std::string::npos);

    // Ignore the space before the hyphen and save the capacity
    std::stringstream ss(remainder);
    ss >> capacity;
}

bool Hospital::isFull() {
    return capacity == numAssigned;
}

std::string Hospital::getName() {
    return name;
}

int Hospital::getIndex() {
    return index;
}

int Hospital::getCapacity() {
    return capacity;
}

int Hospital::getNumAssigned() {
    return numAssigned;
}