#include "resident.h"
#include "hospital.h"
#include "util.h"

#include <iostream>
#include <sstream>

Resident::Resident() {
    // Create the name of the resident and increment the index
    name = "r" + std::to_string(Resident::index);
    Resident::index++;

    hospitalPreferences = new List<Hospital*>();
}

Resident::~Resident() {
    delete hospitalPreferences;
}

void Resident::addPreferences(std::string preferences, HospitalArr* hospitals) {
    char* ptr;
    // Get the first token
    ptr = strtok(preferences.data(), " ");

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
        hospitalPreferences->append(hospitalNode);

        ptr = strtok(NULL, " ");  
    }
}

std::string Resident::getName() {
    // Return the resident's name
    return name;
}

List<Hospital*>* Resident::getHospitalPreferences() {
    return hospitalPreferences;
}