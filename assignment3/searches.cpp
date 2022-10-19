#include "search.h"

#include <string>
#include "util.h"

int linearSearch(StringArr* data, std::string target, int* comparisons = nullptr) {
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