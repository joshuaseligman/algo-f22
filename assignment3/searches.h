#pragma once

#include <string>
#include "util.h"

// Performs a linear search on the data and counts the number of comparisons
int linearSearch(StringArr* data, std::string target, int* comparisons = nullptr);