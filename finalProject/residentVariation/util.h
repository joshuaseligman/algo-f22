#pragma once

#include <string>

// The number of preferences each resident gets
inline int NUM_PREFERENCES = 0;

// Struct to create string arrays and store their length at the same time
// Especially for use on the heap
struct StringArr {
    std::string* arr;
    int length;
};