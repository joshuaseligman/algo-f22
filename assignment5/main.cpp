#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"
#include "fractionalKnapsack.h"
#include "graphGenerator.h"

int main() {

    StringArr* graphFile = readFile("graphs2.txt");

    createGraphs(graphFile);

    StringArr* spiceFile = readFile("spice.txt");

    fractionalKnapsackAlgo(spiceFile);

    delete [] graphFile->arr;
    delete graphFile;

    delete [] spiceFile->arr;
    delete spiceFile;
   
    return 0;
}