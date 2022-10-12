#include <iostream>

#include "fileUtil.h"
#include "util.h"
#include "stableMatching.h"
#include "resident.h"

int main() {
    StringArr* data = readFile("testData1.txt");

    for (int i = 0; i < data->length; i++) {
        std::cout << data->arr[i] << std::endl;
    }

    ResidentArr* residents = createResidents(10);
    for (int j = 0; j < residents->length; j++) {
        std::cout << residents->arr[j].getName() << std::endl;;
    }

    HospitalArr* hospitals = createHospitals(5);
    for (int j = 0; j < hospitals->length; j++) {
        std::cout << hospitals->arr[j].getName() << std::endl;;
    }


    // Memory management and clean up
    delete [] residents->arr;
    delete residents;

    delete [] hospitals->arr;
    delete hospitals;

    delete [] data->arr;
    delete data;
}