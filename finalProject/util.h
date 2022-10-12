#pragma once

#include "resident.h"

// Struct to create string arrays and store their length at the same time
// Especially for use on the heap
struct StringArr {
    std::string* arr;
    int length;
};

struct ResidentArr {
    Resident* arr;
    int length;
};