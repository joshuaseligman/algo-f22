#include "sort.h"

#include "hospital.h"

void quickSortWithIndices(Resident** data, int start, int end) {
    // Base case for arrays of size 1 or 0
    if (start >= end) {
        // No work is needed
        return;
    }

    // The variable used for the pivot index
    int pivotIndex;

    if (end - start < 3) {
        // Array of size 2 should take either element as it will need exactly 1 more divide regardless of the pivot
        pivotIndex = start;
    } else {
        // Generate 3 random indices that are all unique to use to pick a pivot
        int pivotChoice1 = rand() % (end - start) + start;
        int pivotChoice2 = rand() % (end - start) + start;
        while (pivotChoice2 != pivotChoice1) {
            pivotChoice2 = rand() % (end - start) + start;
        }
        int pivotChoice3 = rand() % (end - start) + start;
        while (pivotChoice3 != pivotChoice1 && pivotChoice3 != pivotChoice2) {
            pivotChoice3 = rand() % (end - start) + start;
        }

        // Find the median of the 3 indices picked and set the pivot index appropriately
        // This will hopefully create balanced partitions regardless of the status of the array
        if (data[pivotChoice1]->compare(data[pivotChoice2]) <= 0 && data[pivotChoice1]->compare(data[pivotChoice3]) >= 0) {
            pivotIndex = pivotChoice1;
        } else if (data[pivotChoice1]->compare(data[pivotChoice3]) <= 0 && data[pivotChoice1]->compare(data[pivotChoice2]) >= 0) {
            pivotIndex = pivotChoice1;
        } else if (data[pivotChoice2]->compare(data[pivotChoice1]) <= 0 && data[pivotChoice2]->compare(data[pivotChoice3]) >= 0) {
            pivotIndex = pivotChoice2;
        } else if (data[pivotChoice2]->compare(data[pivotChoice1]) >= 0 && data[pivotChoice2]->compare(data[pivotChoice3]) <= 0) {
            pivotIndex = pivotChoice2;
        } else {
            pivotIndex = pivotChoice3;
        }
    }

    // Partition the data around the pivot
    int partitionOut = partition(data, start, end, pivotIndex);

    // Sort each of the partitions
    quickSortWithIndices(data, start, partitionOut - 1);
    quickSortWithIndices(data, partitionOut + 1, end);
}

int partition(Resident** data, int start, int end, int pivotIndex) {
    // Move the pivot to the end of the subarray
    Resident* pivot = data[pivotIndex];
    data[pivotIndex] = data[end];
    data[end] = pivot;

    // We initially do not have any items in the low partition, so make it less than the start
    int lastLowPartitonIndex = start - 1;

    // Iterate through the subarray, excluding the pivot
    for (int i = start; i <= end - 1; i++) {
        // Check if the element is less than the pivot
        if (data[i]->compare(pivot) < 0) {
            // We have an element for the low partition
            lastLowPartitonIndex++;

            // Move the element to the end of the low partition
            Resident* temp = data[i];
            data[i] = data[lastLowPartitonIndex];
            data[lastLowPartitonIndex] = temp;
        }
    }

    // Move the pivot into its appropriate place between the partitions
    data[end] = data[lastLowPartitonIndex + 1];
    data[lastLowPartitonIndex + 1] = pivot;

    return lastLowPartitonIndex + 1;
}