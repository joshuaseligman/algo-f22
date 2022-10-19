#include <iostream>

#include "util.h"
#include "fileUtil.h"
#include "sortsAndShuffles.h"

int main() {
    StringArr* magicItems = readFile("magicItems.txt");

    quickSort(magicItems);

    for (int i = 0; i < magicItems->length; i++) {
        std::cout << magicItems->arr[i] << std::endl;
    }

    delete [] magicItems->arr;
    delete magicItems;
}