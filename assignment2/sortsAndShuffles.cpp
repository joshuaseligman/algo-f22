#include <stdlib.h>
#include <time.h>
#include <string>

#include "sortsAndShuffles.h"
#include "util.h"

int selectionSort(StringArr* data) {
    // Start comparisons at 0
    int comparisons = 0;

    // Iterate through the second to last element because the last element will already be sorted as is
    for (int i = 0; i < data->length - 1; i++) {
        // The smallest index is going to start as the start of the subset of the list
        int smallestIndex = i;

        // Iterate through the rest of the list
        for (int j = i + 1; j < data->length; j++) {
            // Compare the current element to the current smallest element in the subset
            if (data->arr[smallestIndex].compare(data->arr[j]) > 0) {
                // If the current element comes first, make it the new smallest element
                smallestIndex = j;
            }
            // Increment comparisons
            comparisons++;
        }

        // Put the smallest index in its respective place
        std::string temp = data->arr[i];
        data->arr[i] = data->arr[smallestIndex];
        data->arr[smallestIndex] = temp;
    }

    // Return the number of comparisons
    return comparisons;
}

int insertionSort(StringArr* data) {
    // Number of comparisons starts at 0
    int comparisons = 0;

    // We begin with the second element because an array of size 1 is already sorted
    // So no need to check on the first element
    for (int i = 1; i < data->length; i++) {
        // Save the current element for later use
        std::string currentVal = data->arr[i];

        // Comparisons are going to start with the previous index
        int j = i - 1;

        // Continue until j is a valid index (< 0) or until we found an element that is less than the
        // current element that is being sorted
        while (j >= 0 && currentVal.compare(data->arr[j]) < 0) {
            // We made a comparison so increment it
            comparisons++;

            // Shift the compared element over 1 to make room for the element being sorted
            data->arr[j + 1] = data->arr[j];
            j--;
        }

        // After the loop, we want to increment comparisons only if j >= 0 because
        // if j < 0, then the boolean expression would have immediately returned false without making
        // a comparison
        if (j >= 0) {
            comparisons++;
        }

        // Place the value in its proper place
        data->arr[j + 1] = currentVal;
    }

    // Return the number of comparisons
    return comparisons;
}

void mergeSort(StringArr* data, int* comparisons) {
    // Return the number of comparisons from sorting the entire array
    return mergeSortWithIndices(data, 0, data->length - 1, comparisons);
}

void mergeSortWithIndices(StringArr* data, int start, int end, int* comparisons) {
    // Base case is array of size 1 or size 0 (if the list is completely empty)
    if (start >= end) {
        // No work is needed
        return;
    }

    // Get the midpoint for the sections
    int mid = (start + end) / 2;

    // Sort the first half
    mergeSortWithIndices(data, start, mid, comparisons);

    // Sort the second half
    mergeSortWithIndices(data, mid + 1, end, comparisons);

    // Merge both halves
    merge(data, start, end, mid, comparisons);
}

void merge(StringArr* data, int start, int end, int mid, int* comparisons) {
    // The left half is at the start
    int leftIndex = start;

    // The right half starts at the midpoint + 1
    int rightIndex = mid + 1;

    // Get the size of the array that the 2 halves will merge into
    // and create the merged sub array
    int subArrLength = end - start + 1;
    std::string newSubArr[subArrLength];

    // Iterate through the entire merged subarray
    for (int i = 0; i < subArrLength; i++) {
        // If the rightIndex > end, then the entire right half is already merged
        if (rightIndex > end) {
            // Add the next element from the left half
            newSubArr[i] = data->arr[leftIndex];
            leftIndex++;
        } else if (leftIndex > mid) { // If the leftIndex > mid, then the entire left half is already merged
            // Add the next element from the right half
            newSubArr[i] = data->arr[rightIndex];
            rightIndex++;
        } else if (data->arr[leftIndex].compare(data->arr[rightIndex]) < 0) { // Compare the 2 elements from each half
            // Add the next element from the left half
            newSubArr[i] = data->arr[leftIndex];
            leftIndex++;

            // Increment the number of comparisons made
            if (comparisons != nullptr) {
                (*comparisons)++;
            }
        } else {
            // Add the next element from the right half
            newSubArr[i] = data->arr[rightIndex];
            rightIndex++;

            // Make sure to increment comparisons because a comparison was made in the last else-if condition
            if (comparisons != nullptr) {
                (*comparisons)++;
            }
        }
    }

    // Transfer the merged subarray to the actual array
    for (int j = 0; j < subArrLength; j++) {
        data->arr[start + j] = newSubArr[j];
    }
}

void quickSort(StringArr* data, int* comparisons) {
    // Run the helper function for the entire array
    quickSortWithIndices(data, 0, data->length - 1, comparisons);
}

void quickSortWithIndices(StringArr* data, int start, int end, int* comparisons) {
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
        if (data->arr[pivotChoice1] <= data->arr[pivotChoice2] && data->arr[pivotChoice1] >= data->arr[pivotChoice3]) {
            pivotIndex = pivotChoice1;

            // We made 2 comparisons to choose the pivot
            if (comparisons != nullptr) {
                *comparisons += 2;
            }
        } else if (data->arr[pivotChoice1] <= data->arr[pivotChoice3] && data->arr[pivotChoice1] >= data->arr[pivotChoice2]) {
            pivotIndex = pivotChoice1;

            // Estimated 4 comparisons to choose the pivot
            if (comparisons != nullptr) {
                *comparisons += 4;
            }
        } else if (data->arr[pivotChoice2] <= data->arr[pivotChoice1] && data->arr[pivotChoice2] >= data->arr[pivotChoice3]) {
            pivotIndex = pivotChoice2;

            // Estimated 6 comparisons to choose the pivot
            if (comparisons != nullptr) {
                *comparisons += 6;
            }
        } else if (data->arr[pivotChoice2] >= data->arr[pivotChoice1] && data->arr[pivotChoice2] <= data->arr[pivotChoice3]) {
            pivotIndex = pivotChoice2;

            // Estimated 8 comparisons to choose the pivot
            if (comparisons != nullptr) {
                *comparisons += 8;
            }
        } else {
            pivotIndex = pivotChoice3;

            // Estimated 8 comparisons to choose the pivot
            if (comparisons != nullptr) {
                *comparisons += 8;
            }
        }
    }

    // Partition the data around the pivot
    int partitionOut = partition(data, start, end, pivotIndex, comparisons);

    // Sort each of the partitions
    quickSortWithIndices(data, start, partitionOut - 1, comparisons);
    quickSortWithIndices(data, partitionOut + 1, end, comparisons);
}

int partition(StringArr* data, int start, int end, int pivotIndex, int* comparisons) {
    // Move the pivot to the end of the subarray
    std::string pivot = data->arr[pivotIndex];
    data->arr[pivotIndex] = data->arr[end];
    data->arr[end] = pivot;

    // We initially do not have any items in the low partition, so make it less than the start
    int lastLowPartitonIndex = start - 1;

    // Iterate through the subarray, excluding the pivot
    for (int i = start; i <= end - 1; i++) {
        // Check if the element is less than the pivot
        if (data->arr[i].compare(pivot) < 0) {
            // We have an element for the low partition
            lastLowPartitonIndex++;

            // Move the element to the end of the low partition
            std::string temp = data->arr[i];
            data->arr[i] = data->arr[lastLowPartitonIndex];
            data->arr[lastLowPartitonIndex] = temp;
        }
        // Incement comparisons
        if (comparisons != nullptr) {
            (*comparisons)++;
        }
    }

    // Move the pivot into its approprate place between the partitions
    data->arr[end] = data->arr[lastLowPartitonIndex + 1];
    data->arr[lastLowPartitonIndex + 1] = pivot;

    return lastLowPartitonIndex + 1;
}

void knuthShuffle(StringArr* data) {
    // Random numbers found at https://cplusplus.com/reference/cstdlib/rand/
    // Initialize the seed for random numbers to be different each time the program is run
    srand(time(NULL));

    for (int i = 0; i < data->length; i++) {
        // Get the random index where 0 <= swapIndex <= data->length - 1
        int swapIndex = rand() % data->length;

        // Swap the data at the respective indices
        std::string temp = data->arr[i];
        data->arr[i] = data->arr[swapIndex];
        data->arr[swapIndex] = temp;
    }
}