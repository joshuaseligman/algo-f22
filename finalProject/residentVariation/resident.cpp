#include "resident.h"
#include "hospital.h"

#include "list.h"
#include "util.h"

#include <iostream>
#include <sstream>
#include <string>

Resident::Resident() {
    hospitalPreferences = new Hospital*[NUM_PREFERENCES];
    assignment = nullptr;
    curPreferenceIndex = 0;
}

Resident::~Resident() {
    delete [] preferenceArr;
    delete [] hospitalPreferences;
}

void Resident::loadData(std::string data, int resIndex, HospitalArr* hospitals) {
    // The part of the line before the colon is the name
    int colonIndex = data.find(":");
    name = data.substr(0, colonIndex);

    // Set the index of the element (number in string - 1), but quicker to pass the index as is
    index = resIndex;

    // Initialize the array for the preferences
    preferenceArr = new int[hospitals->length];
    for (int i = 0; i < hospitals->length; i++) {
        preferenceArr[i] = 0;
    }

    // Load the preference data
    addPreferences(data.substr(colonIndex + 2, std::string::npos), hospitals);
}

void Resident::addPreferences(std::string preferences, HospitalArr* hospitals) {
    char* ptr;
    // Get the first token
    ptr = strtok(preferences.data(), " ");

    int ranking = NUM_PREFERENCES;

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

        // Save the hospital in the preferences
        hospitalPreferences[NUM_PREFERENCES - ranking] = &hospitals->arr[hospitalIndex];

        // Add the preference to the status array
        preferenceArr[hospitalIndex] = ranking;

        // Moving on to the next ranking
        if (ranking == NUM_PREFERENCES) {
            hospitals->arr[hospitalIndex].incrementFirstChoice();
        }
        ranking--;

        ptr = strtok(NULL, " ");  
    }
}

int Resident::compare(Resident* compResident) {
    // Get the current hospitals being compared
    int thisCur = curPreferenceIndex + 1;
    int otherCur = compResident->getCurPreferenceIndex() + 1;

    // Get the first hospital in the preference list that is still available
    while (thisCur < NUM_PREFERENCES) {
        if (hospitalPreferences[thisCur]->isFull()) {
            thisCur++;
        } else {
            break;
        }
    }

    while (otherCur < NUM_PREFERENCES) {
        if (compResident->getHospitalPreferences()[otherCur]->isFull()) {
            otherCur++;
        } else {
            break;
        }
    }

    // Compute the difference if each resident went to their next available choice
    int thisDiff = thisCur - curPreferenceIndex;
    int otherDiff = otherCur - compResident->getCurPreferenceIndex();

    // Assume they are the same
    int out = 0;

    if (thisDiff < otherDiff) {
        // Lower difference should be put at the end of the list
        out = 1;

        Hospital* target = hospitalPreferences[thisCur];
        bool found = false;
        // Iterate back through all possible moves to go down for the other resident
        for (int i = compResident->getCurPreferenceIndex() + 1; i < NUM_PREFERENCES && !found; i++) {
            // Iterate through all the residents assigned to the hospital
            for (int j = 0; j < compResident->getHospitalPreferences()[i]->getNumAssigned() && !found; j++) {
                Resident* middleMan = compResident->getHospitalPreferences()[i]->getAssignments()[j];
                for (int k = middleMan->getCurPreferenceIndex() + 1; k < NUM_PREFERENCES && !found; k++) {
                    if (middleMan->getHospitalPreferences()[k] == target) {
                        int middleDiff = k - middleMan->getCurPreferenceIndex();
                        int newOtherDiff = i - compResident->getCurPreferenceIndex();
                        double avg = (double) (middleDiff + newOtherDiff) / 2;
                        if (avg < thisDiff) {
                            out = -1;
                            found = true;
                        }
                    }
                }
            }
        }
    } else if (thisDiff > otherDiff) {
        // Higher difference should be kept near the front
        out = -1;

        Hospital* target = compResident->getHospitalPreferences()[otherCur];
        bool found = false;
        // Iterate back through all possible moves to go down for the other resident
        for (int i = curPreferenceIndex + 1; i < NUM_PREFERENCES && !found; i++) {
            // Iterate through all the residents assigned to the hospital
            for (int j = 0; j < hospitalPreferences[i]->getNumAssigned() && !found; j++) {
                Resident* middleMan = hospitalPreferences[i]->getAssignments()[j];
                for (int k = middleMan->getCurPreferenceIndex() + 1; k < NUM_PREFERENCES && !found; k++) {
                    if (middleMan->getHospitalPreferences()[k] == target) {
                        int middleDiff = k - middleMan->getCurPreferenceIndex();
                        int newThisDiff = i - curPreferenceIndex;
                        double avg = (double) (middleDiff + newThisDiff) / 2;
                        if (avg < thisDiff) {
                            out = -1;
                            found = true;
                        }
                    }
                }
            }
        }
    } else {
        // If the differences are the same, prioritize keeping the one that is happier as it is
        if (curPreferenceIndex < compResident->getCurPreferenceIndex()) {
            out = -1;
        } else if (curPreferenceIndex > compResident->getCurPreferenceIndex()) {
            out = 1;
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

Hospital** Resident::getHospitalPreferences() {
    return hospitalPreferences;
}

int Resident::getCurPreferenceIndex() {
    return curPreferenceIndex;
}

void Resident::setCurPreferenceIndex(int newIndex) {
    curPreferenceIndex = newIndex;
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