#include <iostream>

#include "fileUtil.h"
#include "util.h"
#include "sortsAndShuffles.h"

int main() {
    StringArr* magicItems = readFile("magicitems.txt");

    knuthShuffle(magicItems);

    for (int i = 0; i < magicItems->length; i++) {
        std::cout << magicItems->arr[i] << std::endl;
    }

    delete magicItems;

    return 0;
}