#include "resident.h"
#include "hospital.h"

#include "list.h"

#include <iostream>
#include <sstream>
#include <string>

Resident::Resident() {
    hospitalPreferences = new List<Hospital*>();
    assignment = nullptr;
}

Resident::~Resident() {
    delete [] preferenceArr;
    delete hospitalPreferences;
}

void Resident::loadData(std::string data, int resIndex, HospitalArr* hospitals) {
    // The part of the line before the colon is the name
    int colonIndex = data.find(":");
    name = data.substr(0, colonIndex);

    // Set the index of the element (number in string - 1), but quicker to pass the index as is
    index = resIndex;

    // Initialize the array for the preferences
    preferenceArr = new int[hospitals->length];

    // Load the preference data
    addPreferences(data.substr(colonIndex + 2, std::string::npos), hospitals);
}

void Resident::addPreferences(std::string preferences, HospitalArr* hospitals) {
    char* ptr;
    // Get the first token
    ptr = strtok(preferences.data(), " ");

    int ranking = Hospital::NUM_LEVELS;

    // Continue until the end of the string  
    while (ptr != NULL) {
        // Create the string stream and remove the first character ('h')
        std::stringstream ss(ptr);
        ss.get();

        // Get the hospital index
        int hospitalIndex;
        ss >> hospitalIndex;

        // Decrement because the first hospital is labeled as h1, but stored in index 0
        hospitalIndex--;

        // Create a node and add it to the end of the preferences list because the preferences are in order
        Node<Hospital*>* hospitalNode = new Node<Hospital*>(&hospitals->arr[hospitalIndex]);
        hospitalPreferences->enqueue(hospitalNode);

        // Add the preference to the status array
        preferenceArr[hospitalIndex] = ranking;

        // Add the ranking to the hospital level
        hospitalNode->data->setPriority(hospitalNode->data->getPriority() + ranking);
        ranking--;

        ptr = strtok(NULL, " ");  
    }
}

int Resident::getIndex() {
    return index;
}

std::string Resident::getName() {
    // Return the resident's name
    return name;
}

List<Hospital*>* Resident::getHospitalPreferences() {
    return hospitalPreferences;
}

int* Resident::getPreferencesArr() {
    return preferenceArr;
}

Hospital* Resident::getAssignment() {
    return assignment;
}

void Resident::setAssignment(Hospital* newAssignment) {
    assignment = newAssignment;
}