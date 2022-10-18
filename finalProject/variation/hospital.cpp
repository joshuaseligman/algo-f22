#include "hospital.h"
#include "resident.h"
#include "list.h"

#include <string>
#include <sstream>
#include <iostream>

Hospital::Hospital() {
    // Initialize leveledAssignments to be NUM_LEVELS of empty lists
    leveledAssignments = new List<Resident*>[NUM_LEVELS];
}

Hospital::~Hospital() {
    delete [] leveledAssignments;
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

void Hospital::addResident(Resident* resident, int level) {
    // Create a node and add it to the level
    Node<Resident*>* residentNode = new Node<Resident*>(resident);
    leveledAssignments[level].enqueue(residentNode);

    // Assign the resident to this hospital
    resident->setAssignment(this);
}

bool Hospital::isFull() {
    return capacity == getNumAssigned();
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
    int sum = 0;
    // Add up the number of residents in each level and return it
    for (int i = 0; i < NUM_LEVELS; i++) {
        sum += leveledAssignments[i].getSize();
    }
    return sum;
}

List<Resident*>* Hospital::getAssignments() {
    return leveledAssignments;
}