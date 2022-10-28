#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"

#include "stdlib.h"
#include "time.h"

#include <iostream>

int main() {
    // Set the seed for the random numbers
    srand(time(NULL));

    StringArr* data = readFile("testData7.txt");
    
    stableMatchAlgo(data);

    delete [] data->arr;
    delete data;
}