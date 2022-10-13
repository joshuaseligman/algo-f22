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

    delete [] assignedResidents;
}

void Hospital::loadData(std::string data, int hospIndex, ResidentArr* residents) {
    // The part of the line before the colon is the name
    int colonIndex = data.find(":");
    name = data.substr(0, colonIndex);

    // Set the index of the element (number in string - 1), but quicker to pass the index as is
    index = hospIndex;

    // Initialize the preferences array to be the number of residents
    residentPreferences = new int[residents->length];
    // Initialize everything to be 0 (does not want the resident at all)
    for (int i = 0; i < residents->length; i++) {
        residentPreferences[i] = 0;
    }

    // Get the remainder of the string after the colon and the space
    std::string remainder = data.substr(colonIndex + 2, std::string::npos);
    int hyphenIndex = remainder.find("-");

    // Ignore the space before the hyphen and save the capacity
    std::string capacityStr = remainder.substr(0, hyphenIndex - 1);
    std::stringstream ss(capacityStr);
    ss >> capacity;

    assignedResidents = new Resident[capacity];

    addPreferences(remainder.substr(hyphenIndex + 2, std::string::npos), residents);
}

void Hospital::addPreferences(std::string preferences, ResidentArr* residents) {
    char* ptr;
    // Get the first token
    ptr = strtok(preferences.data(), " ");

    // Initialize the current preference to be 1 (lower is better) (0 is does not want the resident)
    int curPreference = 1;

    // Continue until the end of the string  
    while (ptr != NULL) {
        // Create the string stream and remove the first character ('h')
        std::stringstream ss(ptr);
        ss.get();

        // Get the hospital index
        int residentIndex;
        ss >> residentIndex;

        // Decrement because the first hospital is labeled as h1, but stored in index 0
        residentIndex--;

        // Set the preference within the array
        residentPreferences[residentIndex] = curPreference;
        curPreference++;

        ptr = strtok(NULL, " ");  
    }
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