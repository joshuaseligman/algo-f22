#include <iostream>

#include "fileUtil.h"
#include "util.h"

int main() {
    StringArr* data = readFile("testData1.txt");

    for (int i = 0; i < data->length; i++) {
        std::cout << data->arr[i] << std::endl;
    }

    delete data;
}