#pragma once

#include "resident.h"
#include "hospital.h"

// Struct to create string arrays and store their length at the same time
// Especially for use on the heap
struct StringArr {
    std::string* arr;
    int length;
};

// Struct for creating an array of residents on the heap
struct ResidentArr {
    Resident* arr;
    int length;
};

// Struct for working with hospitals on the heap
struct HospitalArr {
    Hospital* arr;
    int length;
};