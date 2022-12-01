#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"
#include "fractionalKnapsack.h"
#include "graphGenerator.h"

int main() {

    StringArr* graphFile = readFile("graphs2.txt");

    createGraphs(graphFile);

    std::cout << std::endl;

    StringArr* graphFileTest = readFile("graphs3.txt");
    createGraphs(graphFileTest);

    std::cout << std::endl;

    StringArr* spiceFile = readFile("spice.txt");
    fractionalKnapsackAlgo(spiceFile);

    std::cout << std::endl;

    StringArr* spiceFileTest1 = readFile("spiceTest1.txt");
    fractionalKnapsackAlgo(spiceFileTest1);

    StringArr* spiceFileTest2 = readFile("spiceTest2.txt");
    fractionalKnapsackAlgo(spiceFileTest2);


    delete [] graphFile->arr;
    delete graphFile;

    delete [] graphFileTest->arr;
    delete graphFileTest;

    delete [] spiceFile->arr;
    delete spiceFile;

    delete [] spiceFileTest1->arr;
    delete spiceFileTest1;

    delete [] spiceFileTest2->arr;
    delete spiceFileTest2;

    return 0;
}