#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"

#include <iostream>

int main() {
    StringArr* data = readFile("testData2.txt");
    
    stableMatchAlgo(data);

    delete [] data->arr;
    delete data;
}
