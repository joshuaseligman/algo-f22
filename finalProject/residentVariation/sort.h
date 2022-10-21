#include "hospital.h"

// Sort the entire array of hospitals
void quickSort(HospitalArr* data);

// Sort the array of hospitals, given the subarray to work with
void quickSortWithIndices(HospitalArr* data, int start, int end);

// Partition the array
int partition(HospitalArr* data, int start, int end, int pivotIndex);