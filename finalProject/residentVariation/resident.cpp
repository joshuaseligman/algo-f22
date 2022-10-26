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

        // Moving on to the next ranking
        if (ranking == Hospital::NUM_LEVELS) {
            hospitalNode->data->incrementFirstChoice();
        }
        ranking--;

        ptr = strtok(NULL, " ");  
    }
}

int Resident::compare(Resident* compResident, int level) {
    // Get the current hospitals being compared
    Node<Hospital*>* thisCur = getHospitalPreferences()->getHead();
    Node<Hospital*>* otherCur = compResident->getHospitalPreferences()->getHead();

    // Assume we are working with a later level
    bool firstLevel = false;

    if (level == 0) {
        thisCur = thisCur->next;
        otherCur = otherCur->next;

        firstLevel = true;
    }

    // Assume they are the same
    int out = 0;

    // Continue to compare the hospitals until no more exist
    while (thisCur != nullptr && otherCur != nullptr) {
        if (firstLevel) {
            if (thisCur->data->getFirstChoiceCount() >= thisCur->data->getCapacity() && otherCur->data->getFirstChoiceCount() < otherCur->data->getCapacity()) {
                // Check if one of the hospitals is full and the other is not to prioritize taking advantage of open spaces
                out = 1;
                break;
            } else if (thisCur->data->getFirstChoiceCount() < thisCur->data->getCapacity() && otherCur->data->getFirstChoiceCount() >= otherCur->data->getCapacity()) {
                out = -1;
                break;
            } else {
                // Try the next level if the hospitals are the same
                thisCur = thisCur->next;
                otherCur = otherCur->next;
            }
        } else {
            if (thisCur->data->isFullRange(level - 1) && !otherCur->data->isFullRange(level - 1)) {
                // Check if one of the hospitals is full and the other is not to prioritize taking advantage of open spaces
                out = 1;
                break;
            } else if (!thisCur->data->isFullRange(level - 1) && otherCur->data->isFullRange(level - 1)) {
                out = -1;
                break;
            } else {
                // Try the next level if the hospitals are the same
                thisCur = thisCur->next;
                otherCur = otherCur->next;
            }
        }
    }
    
    return out;
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