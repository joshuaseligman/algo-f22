#include <stdlib.h>
#include <time.h>
#include <string>

#include "sortsAndShuffles.h"
#include "util.h"

int selectionSort(StringArr* data) {
    return 0;
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