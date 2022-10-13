#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"

#include <iostream>

int main() {
    StringArr* data = readFile("testData1.txt");

    for (int i = 0; i < data->length; i++) {
        std::cout << data->arr[i] << std::endl;
    }

    // stableMatchAlgo(data);

    delete [] data->arr;
    delete data;
}