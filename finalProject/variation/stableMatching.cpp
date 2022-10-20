#include "stableMatching.h"
#include "resident.h"
#include "hospital.h"
#include "util.h"
#include "sort.h"

#include <iostream>
#include <sstream>

void stableMatchAlgo(StringArr* data) {
    // String split code from: https://www.javatpoint.com/how-to-split-strings-in-cpp
    // A pointer to each part of the split string
    char* ptr;
    // Get the first token
    ptr = strtok(data->arr[0].data(), " ");

    int numResidents = -1;
    int numHospitals = -1;

    // Continue until the end of the string  
    while (ptr != NULL) {
        // String to integer conversion https://www.geeksforgeeks.org/converting-strings-numbers-c-cpp/
        std::stringstream ss(ptr);
        if (ss.str().compare("Config:") != 0) {
            if (numResidents == -1) {
                ss >> numResidents;
            } else {
                ss >> numHospitals;
            }
        }
        ptr = strtok(NULL, " ");  
    }

    std::cout << numResidents << " " << numHospitals << std::endl;

    // Create default residents and hospitals with no preferencs and no capacity
    ResidentArr* residents = createResidents(numResidents);
    HospitalArr* hospitals = createHospitals(numHospitals);

    for (int i = 0; i < residents->length; i++) {
        residents->arr[i].loadData(data->arr[i + 1], i, hospitals);
    }

    for (int i = 0; i < hospitals->length; i++) {
        hospitals->arr[i].loadData(data->arr[residents->length + 1 + i], i, residents);
    }

    for (int i = 0; i < residents->length; i++) {
        residents->arr[i].getHospitalPreferences()->printList();

        for (int j = 0; j < hospitals->length; j++) {
            std::cout << residents->arr[i].getPreferencesArr()[j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < hospitals->length; i++) {
        std::cout << hospitals->arr[i].getName() << "; capacity: " << hospitals->arr[i].getCapacity() << std::endl;

        for (int j = 0; j < hospitals->arr[j].NUM_LEVELS; j++) {
            hospitals->arr[i].getAssignments()[j].printList();
        }
    }

    // Call the actual algorithm
    generateStableMatches(residents, hospitals);

    // Memory management and clean up
    delete [] residents->arr;
    delete residents;

    for (int i = 0; i < hospitals->length; i++) {
        hospitals->arr[i].clearMemory();
    }
    delete [] hospitals->arr;
    delete hospitals;
}

ResidentArr* createResidents(int numResidents) {
    // Create an array of default residents
    Resident* resArr = new Resident[numResidents];

    // Create the wrapper object and return it
    ResidentArr* output = new ResidentArr;
    output->arr = resArr;
    output->length = numResidents;

    return output;
}

HospitalArr* createHospitals(int numHospitals) {
    // Create an array of default hospitals
    Hospital* hosArr = new Hospital[numHospitals];

    // Create the wrapper object and return it
    HospitalArr* output = new HospitalArr;
    output->arr = hosArr;
    output->length = numHospitals;

    return output;
}

void generateStableMatches(ResidentArr* residents, HospitalArr* hospitals) {
    std::cout << std::endl;

   for (int i = 0; i < residents->length; i++) {
        Node<Hospital*>* cur = residents->arr[i].getHospitalPreferences()->getHead();

        int level = 0;

        while (cur != nullptr) {
            // Provisionally assign the resident to all of its preferences
            cur->data->addResident(&residents->arr[i], level);
            level++;
            cur = cur->next;
        }
    }

    // Print out the number of residents in each level for each hospital
    for (int i = 0; i < hospitals->length; i++) {
        std::cout << hospitals->arr[i].getCapacity() << ": ";
        for (int j = 0; j < hospitals->arr[i].NUM_LEVELS; j++) {
            std::cout << hospitals->arr[i].getAssignments()[j].getSize() << " ";
        }
        std::cout << "= " << hospitals->arr[i].getNumAssigned() << std::endl;
    }

    quickSort(hospitals);

    for (int i = 0; i < hospitals->length; i++) {
        std::cout << hospitals->arr[i].getName() << " ";
    }
    std::cout << std::endl;

    // std::cout << "Finished algo" << std::endl << std::endl;

    // Print the final results
    // std::cout << "Final results:" << std::endl;
    // for (int i = 0; i < residents->length; i++) {
    //     if (residents->arr[i].getAssignment() != nullptr) {
    //         std::cout << "(" << residents->arr[i].getName() << ", " << residents->arr[i].getAssignment()->getName() << ")" << std::endl;
    //     } else {
    //         std::cout << "(" << residents->arr[i].getName() << ", nullptr)" << std::endl;
    //     }
    // }
}