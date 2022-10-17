#include "hospital.h"
#include "resident.h"

#include <string>
#include <sstream>
#include <iostream>

Hospital::Hospital() {
    // Initialize these variables to be nothing
    numAssigned = 0;
    lowestPreferredAssignedResidentIndex = -1;
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
    // Initialize everything to be 0 (does not want the resident at all)
    for (int i = 0; i < residents->length; i++) {
        residentPreferences[i] = INT_MAX;
    }

    // Get the remainder of the string after the colon and the space
    std::string remainder = data.substr(colonIndex + 2, std::string::npos);
    int hyphenIndex = remainder.find("-");

    // Ignore the space before the hyphen and save the capacity
    std::string capacityStr = remainder.substr(0, hyphenIndex - 1);
    std::stringstream ss(capacityStr);
    ss >> capacity;

    assignedResidents = new Resident[capacity];

    // Clear the assigned residents array
    for (int i = 0; i < capacity; i++) {
        assignedResidents[i].~Resident();
    }

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

bool Hospital::isFull() {
    return capacity == numAssigned;
}

void Hospital::replaceLowest(Resident* newResident) {
    // Add the new resident to where the lowest resident is currently
    assignedResidents[lowestPreferredAssignedResidentIndex] = *newResident;
    newResident->setAssignment(this);

    // Update the lowest assigned resident index
    setLowestPreferredAssignedResidentIndex();
}

void Hospital::addResident(Resident* newResident) {
    // Add the resident to the array
    assignedResidents[numAssigned] = *newResident;
    newResident->setAssignment(this);
    numAssigned++;

    // Update the lowest assigned resident index
    setLowestPreferredAssignedResidentIndex();
}

void Hospital::setLowestPreferredAssignedResidentIndex() {
    int lowestIndex = 0;

    // Iterate through the array to find the worst preferred resident assigned to the hospital
    for (int i = 1; i < numAssigned; i++) {
        if (residentPreferences[assignedResidents[i].getIndex()] > residentPreferences[assignedResidents[lowestIndex].getIndex()]) {
            lowestIndex = i;
        }
    }
    // Update the value
    lowestPreferredAssignedResidentIndex = lowestIndex;
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

int* Hospital::getResidentPreferences() {
    return residentPreferences;
}

Resident* Hospital::getAssignedResidents() {
    return assignedResidents;
}

int Hospital::getLowestPreferredAssignedResidentIndex() {
    return lowestPreferredAssignedResidentIndex;
}