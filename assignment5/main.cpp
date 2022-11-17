#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"
#include "fractionalKnapsack.h"

int main() {

    StringArr* spiceFile = readFile("spice.txt");

    fractionalKnapsackAlgo(spiceFile);

    delete [] spiceFile->arr;
    delete spiceFile;
   
    return 0;
}