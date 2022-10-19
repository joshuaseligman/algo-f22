#include "searches.h"

#include <string>
#include "util.h"

int linearSearch(StringArr* data, std::string target, int* comparisons) {
    // Start with the first element in the array
    int i = 0;

    // Iterate through the array, looking for the target
    while (i < data->length && data->arr[i].compare(target) != 0) {
        if (comparisons != nullptr) {
            // Increment the number of comparisons
            (*comparisons)++;
        }
        i++;
    }

    // Default to -1 as the output if the target is not in the array
    int out = -1;

    // Add a comparison and set the index because we found the element
    if (i < data->length) {
        (*comparisons)++;
        out = i;
    }

    // Return the position of the target element
    return out;
}

int binarySearch(StringArr* data, std::string target, int* comparisons) {
    // Call the helper function to perform the binary search, starting off with the entire array
    return binarySearchHelper(data, target, 0, data->length - 1, comparisons);
}

int binarySearchHelper(StringArr* data, std::string target, int start, int stop, int* comparisons) {
    // Do integer division to get the midpoint of the array we are considering
    int mid = (start + stop) / 2;

    // Assume nothing is found, which initializes it to 0
    int out = -1;

    // Only search if start <= stop. Otherwise, the element doesn't exist ond out is already set to -1
    if (start <= stop) {
        if (target.compare(data->arr[mid]) == 0) {
            // Increment the number of comparisons
            (*comparisons)++;

            // The index was found, which is the midpoint
            out = mid;
        } else if (target.compare(data->arr[mid]) < 0) {
            // We have made 2 comparisons
            *comparisons += 2;

            // Run the binary search on the first half of the array
            out = binarySearchHelper(data, target, start, mid - 1, comparisons);
        } else {
            *comparisons += 2;

            // Run the binary search on the second half of the array
            out = binarySearchHelper(data, target, mid + 1, stop, comparisons);
        }
    }

    // Return the index of the element
    return out;
}