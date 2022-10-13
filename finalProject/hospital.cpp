#include "hospital.h"
#include "resident.h"

#include <string>
#include <sstream>
#include <iostream>

Hospital::Hospital() {
    // Initialize these variables to be nothing
    numAssigned = 0;
    lowestPreferredAssignedResident = nullptr;
}

Hospital::~Hospital() {
    delete [] residentPreferences;
}

void Hospital::loadData(std::string data, int hospIndex, ResidentArr* residents) {
    // The part of the line before the colon is the name
    int colonIndex = data.find(":");
    name = data.substr(0, colonIndex);

    // Set the index of the element (number in string - 1), but quicker to pass the index as is
    index = hospIndex;

    // Initialize the preferences array to be the number of residents
    residentPreferences = new int[residents->length];

    // Get the remainder of the string after the colon and the space
    std::string remainder = data.substr(colonIndex + 2, std::string::npos);
    int hyphenIndex = remainder.find("-");

    // Ignore the space before the hyphen
    std::string capacityStr = remainder.substr(0, hyphenIndex - 1);
    std::stringstream ss(capacityStr);
    ss >> capacity;

    std::cout << name << " " << index << " " << capacity << std::endl;
}

void Hospital::addPreferences(std::string preferences, ResidentArr* residents) {

}

std::string Hospital::getName() {
    // Return the hospital's name
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

int* Hospital::getResidentPreferences() {
    return residentPreferences;
}

Resident* Hospital::getAssignedResidents() {
    return assignedResidents;
}

Resident* Hospital::getLowestPreferredAssignedResident() {
    return lowestPreferredAssignedResident;
}