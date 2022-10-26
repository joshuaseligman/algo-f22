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
}

void Hospital::clearMemory() {
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
    leveledAssignments[level].priorityAdd(residentNode, level);
}

void Hospital::removeResident(Resident* resident, int level) {
    // Create a node and add it to the level
    leveledAssignments[level].remove(resident);
}

int Hospital::compare(Hospital* hospitalComp) {
    // Initialize the comparison to be equal to each other
    int out = 0;
    
    // Compute the difference between the number of provisionally assigned residents and the capacity
    int thisDiff = this->getNumAssigned() - this->getCapacity();
    int otherDiff = hospitalComp->getNumAssigned() - hospitalComp->getCapacity();

    if (thisDiff < otherDiff) {
        // This hospital is less than hospitalComp, so set out to -1
        out = -1;
    } else if (thisDiff > otherDiff) {
        // This hospital is greater than hospitalComp, so set out to 1
        out = 1;
    } else { // They both have the same number of provisionally assigned residents
        if (this->getCapacity() < hospitalComp->getCapacity()) {
            // This hospital is less than hospitalComp, so set out to -1
            out = -1;
        } else if (this->getCapacity() > hospitalComp->getCapacity()) {
            // This hospital is greater than hospitalComp, so set out to 1
            out = 1;
        }
    }

    // Return the result of the comparison
    return out;
}

bool Hospital::isFull() {
    return capacity <= getNumAssigned();
}

bool Hospital::isFullRange(int lastLevel) {
    return capacity <= getNumAssignedRange(lastLevel);
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
    for (int i = 0; i < Hospital::NUM_LEVELS; i++) {
        sum += leveledAssignments[i].getSize();
    }
    return sum;
}

int Hospital::getNumAssignedRange(int lastLevel) {
    if (lastLevel >= Hospital::NUM_LEVELS) {
        throw std::invalid_argument("Invalid level. Must be less than " + std::to_string(Hospital::NUM_LEVELS));
        return -1;
    }
    int sum = 0;
    for (int i = 0; i <= lastLevel; i++) {
        sum += leveledAssignments[i].getSize();
    }
    return sum;
}

List<Resident*>* Hospital::getAssignments() {
    return leveledAssignments;
}

int Hospital::getFirstChoiceCount() {
    return firstChoice;
}

void Hospital::incrementFirstChoice() {
    firstChoice++;
}