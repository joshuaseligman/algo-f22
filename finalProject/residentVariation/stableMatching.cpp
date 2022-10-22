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

    // Create default residents and hospitals with no preferencs and no capacity
    ResidentArr* residents = createResidents(numResidents);
    HospitalArr* hospitals = createHospitals(numHospitals);

    for (int i = 0; i < residents->length; i++) {
        residents->arr[i].loadData(data->arr[i + 1], i, hospitals);
    }

    for (int i = 0; i < hospitals->length; i++) {
        hospitals->arr[i].loadData(data->arr[residents->length + 1 + i], i, residents);
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

        // Add each resident to their top choice hospital
        cur->data->addResident(&residents->arr[i], 0);
    }

    for (int i = 0; i < hospitals->length; i++) {
        hospitals->arr[i].getAssignments()[0].printList();
    }

    for (int i = 0; i < hospitals->length; i++) {
        std::cout << hospitals->arr[i].getPriority() << std::endl;
    }

    // Go through each level of the hospitals
    for (int i = 0; i < Hospital::NUM_LEVELS; i++) {
        for (int j = 0; j < hospitals->length; j++) {
            hospitals->arr[j].getAssignments()[i].printList();
            // Make sure the hospital is not over capacity
            while (hospitals->arr[j].getNumAssigned() > hospitals->arr[j].getCapacity()) {
                // If the level is empty, it's ok to quit because the lower levels are causing it to go over, which will be handled in a later iteration
                if (!hospitals->arr[j].getAssignments()[i].isEmpty()) {
                    // Get the resident and remove the hospital from its list
                    Node<Resident*>* res = hospitals->arr[j].getAssignments()[i].dequeue();
                    res->data->getHospitalPreferences()->dequeue();

                    // Add the resident to its next preferred hospital if possible
                    if (i < Hospital::NUM_LEVELS - 1) {
                        res->data->getHospitalPreferences()->getHead()->data->getAssignments()[i + 1].priorityAdd(res, i + 1);
                    } else {
                        delete res;
                    }
                } else {
                    break;
                }
            }
        }
    }

    // Formally assign each resident to the hospitals
    for(int i = 0; i < hospitals->length; i++) {
        for (int j = 0; j < Hospital::NUM_LEVELS; j++) {
            Node<Resident*>* cur = hospitals->arr[i].getAssignments()[j].getHead();
            while (cur != nullptr) {
                cur->data->setAssignment(&hospitals->arr[i]);
                cur = cur->next;
            }
        }
    }

    std::cout << "Finished algo" << std::endl << std::endl;

    // // Print the final results
    std::cout << "Final results:" << std::endl;
    for (int i = 0; i < residents->length; i++) {
        if (residents->arr[i].getAssignment() != nullptr) {
            std::cout << "(" << residents->arr[i].getName() << ", " << residents->arr[i].getAssignment()->getName() << ")" << std::endl;
        } else {
            std::cout << "(" << residents->arr[i].getName() << ", nullptr)" << std::endl;
        }
    }
    std::cout << std::endl;

    // Compute the happiness indices for both residents and hospitals
    std::cout << "Resident Happiness: " << computeResidentHappiness(residents) << std::endl;
    std::cout << "Hospital Happiness: " << computeHospitalHappiness(hospitals) << std::endl;
}

double computeResidentHappiness(ResidentArr* residents) {
    int sum = 0;

    // Go through each resident
    for (int i = 0; i < residents->length; i++) {
        if (residents->arr[i].getAssignment() != nullptr) {
            // Add the preference ranking to the sum
            sum += residents->arr[i].getPreferencesArr()[residents->arr[i].getAssignment()->getIndex()];
        }
    }

    // Take the average of ranking / number of levels
    return (double) sum / (residents->length * Hospital::NUM_LEVELS);
}

double computeHospitalHappiness(HospitalArr* hospitals) {
    double sum = 0;

    for (int i = 0; i < hospitals->length; i++) {
        // The happiness ranking is the percentage of seats that are filled
        sum += (double) hospitals->arr[i].getNumAssigned() / hospitals->arr[i].getCapacity();
    }

    // Return the average happiness ranking
    return sum / hospitals->length;
}