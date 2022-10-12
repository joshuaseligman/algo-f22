#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"

int main() {
    StringArr* data = readFile("testData1.txt");

    stableMatchAlgo(data);

    delete [] data->arr;
    delete data;
}