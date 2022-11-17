#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"

int main() {

    StringArr* spiceFile = readFile("spice.txt");

    for (int i = 0; i < spiceFile->length; i++) {
        std::cout << spiceFile->arr[i] << std::endl;
    }

    delete [] spiceFile->arr;
    delete spiceFile;
   
    return 0;
}