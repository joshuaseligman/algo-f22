#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"

#include <iostream>

int main() {
    StringArr* data = readFile("testData5.txt");
    
    stableMatchAlgo(data);

    delete [] data->arr;
    delete data;
}
