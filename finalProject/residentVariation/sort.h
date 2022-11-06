#include "resident.h"

// Sort the array of residents, given the subarray to work with
void quickSortWithIndices(Resident** data, int start, int end);

// Partition the array
int partition(Resident** data, int start, int end, int pivotIndex);