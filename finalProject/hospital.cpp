#include "hospital.h"

Hospital::Hospital() {
    // Create the name of the hospital and increment the index
    name = "h" + std::to_string(Hospital::index);
    Hospital::index++;
}

std::string Hospital::getName() {
    // Return the hospital's name
    return name;
}