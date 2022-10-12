#include "resident.h"

Resident::Resident() {
    // Create the name of the resident and increment the index
    name = "r" + std::to_string(Resident::index);
    Resident::index++;
}

std::string Resident::getName() {
    // Return the resident's name
    return name;
}