#pragma once

#include <string>
#include "util.h"

// Performs a linear search on the data and counts the number of comparisons
int linearSearch(StringArr* data, std::string target, int* comparisons = nullptr);

// Performs a binary search on the data and counts the number of comparisons
int binarySearch(StringArr* data, std::string target, int* comparisons = nullptr);

// Helper function for the binary search
int binarySearchHelper(StringArr* data, std::string target, int start, int stop, int* comparisons = nullptr);