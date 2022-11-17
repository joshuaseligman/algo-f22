#include <stdlib.h>
#include <time.h>

#include "sort.h"
#include "util.h"
#include "spice.h"

void quickSort(SpiceArr* data){
    quickSortWithIndices(data, 0, data->length - 1);
}

void quickSortWithIndices(SpiceArr* data, int start, int end) {
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
        // Initialize random seed
        srand(time(NULL));

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
        if (data->arr[pivotChoice1]->getUnitPrice() <= data->arr[pivotChoice2]->getUnitPrice() && data->arr[pivotChoice1] >= data->arr[pivotChoice3]) {
            pivotIndex = pivotChoice1;
        } else if (data->arr[pivotChoice1]->getUnitPrice() <= data->arr[pivotChoice3]->getUnitPrice() && data->arr[pivotChoice1]->getUnitPrice() >= data->arr[pivotChoice2]->getUnitPrice()) {
            pivotIndex = pivotChoice1;
        } else if (data->arr[pivotChoice2]->getUnitPrice() <= data->arr[pivotChoice1]->getUnitPrice() && data->arr[pivotChoice2]->getUnitPrice() >= data->arr[pivotChoice3]->getUnitPrice()) {
            pivotIndex = pivotChoice2;
        } else if (data->arr[pivotChoice2]->getUnitPrice() >= data->arr[pivotChoice1]->getUnitPrice() && data->arr[pivotChoice2]->getUnitPrice() <= data->arr[pivotChoice3]->getUnitPrice()) {
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

int partition(SpiceArr* data, int start, int end, int pivotIndex) {
    // Run the helper function for the entire array
    // Move the pivot to the end of the subarray
    Spice* pivot = data->arr[pivotIndex];
    data->arr[pivotIndex] = data->arr[end];
    data->arr[end] = pivot;

    // We initially do not have any items in the low partition, so make it less than the start
    int lastLowPartitonIndex = start - 1;

    // Iterate through the subarray, excluding the pivot
    for (int i = start; i <= end - 1; i++) {
        // Check if the element is greater than the pivot (spices have to be sorted in descending order)
        if (data->arr[i]->getUnitPrice() > pivot->getUnitPrice()) {
            // We have an element for the low partition
            lastLowPartitonIndex++;

            // Move the element to the end of the low partition
            Spice* temp = data->arr[i];
            data->arr[i] = data->arr[lastLowPartitonIndex];
            data->arr[lastLowPartitonIndex] = temp;
        }
    }

    // Move the pivot into its appropriate place between the partitions
    data->arr[end] = data->arr[lastLowPartitonIndex + 1];
    data->arr[lastLowPartitonIndex + 1] = pivot;

    return lastLowPartitonIndex + 1;
}