#include <iostream>

#include "fileUtil.h"
#include "util.h"

int main() {
    StringArr* magicItems = readFile("magicitems.txt");

    for (int i = 0; i < magicItems->length; i++) {
        std::cout << magicItems->arr[i] << std::endl;
    }

    delete [] magicItems->arr;
    delete magicItems;

    return 0;
}