#pragma once

#include "spice.h"

// Quicksort function
void quickSort(SpiceArr* data);

// Helper function for quicksort
void quickSortWithIndices(SpiceArr* data, int start, int end);

// Helper function to partition the array in quicksort
int partition(SpiceArr* data, int start, int end, int pivotIndex);