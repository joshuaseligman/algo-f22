#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"

#include "stdlib.h"
#include "time.h"

#include <iostream>

int main() {
    // Set the seed for the random numbers
    srand(time(NULL));

    std::string file = "testData8.txt";

    std::cout << "Using " << file << std::endl << std::endl;
    StringArr* data = readFile(file);
    
    stableMatchAlgo(data);

    delete [] data->arr;
    delete data;
}
