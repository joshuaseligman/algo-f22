#pragma once

#include <string>

// Forward declarations to prevent circular dependencies
class Resident;
class Hospital;

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