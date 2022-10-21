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

        int level = 0;

        while (cur != nullptr) {
            // Provisionally assign the resident to all of its preferences
            cur->data->addResident(&residents->arr[i], level);

            level++;
            cur = cur->next;
        }
    }

    // A new HospitalArr object whose objects can be moved around without impacting the resident preferences
    HospitalArr mutableHospitals;
    mutableHospitals.arr = new Hospital[hospitals->length];
    mutableHospitals.length = hospitals->length;

    // Initally set each index to map to the hospital in the main array
    for (int i = 0; i < hospitals->length; i++) {
        mutableHospitals.arr[i] = hospitals->arr[i];
    }

    for (int i = 0; i < mutableHospitals.length; i++) {
        // Do a sort on the array, ignoring the hospitals already assigned (front of the array)
        quickSortWithIndices(&mutableHospitals, i, mutableHospitals.length - 1);

        // Print out the number of residents in each level for each hospital
        for (int m = 0; m < mutableHospitals.length; m++) {
            std::cout << mutableHospitals.arr[m].getName() << "(" << mutableHospitals.arr[m].getCapacity() << ") -  ";
            for (int n = 0; n < mutableHospitals.arr[m].NUM_LEVELS; n++) {
                std::cout << mutableHospitals.arr[m].getAssignments()[n].getSize() << " ";
            }
            std::cout << "= " << mutableHospitals.arr[m].getNumAssigned() << std::endl;
        }

        // This is the hospital we are working with
        Hospital* nextHospital = &mutableHospitals.arr[i];

        // Create a counter for the number of residents that have been formally assigned to the hospital so far
        int count = 0;

        // Iterate through each of the levels from top to bottom (to maximize the preferences)
        for (int j = 0; j < Hospital::NUM_LEVELS; j++) {
            nextHospital->getAssignments()[j].printList();

            // Start at the head of the list
            Node<Resident*>* cur = nextHospital->getAssignments()[j].getHead();

            // Go through the entire list
            while (cur != nullptr) {
                // Check to see if we still have room
                if (count < nextHospital->getCapacity()) {
                    // Set the formal assignment
                    cur->data->setAssignment(nextHospital);
                    std::cout << "Formally assigned " << cur->data->getName() << " to " << nextHospital->getName() << std::endl;

                    // Increment the counter since one more resident has been formally assigned
                    count++;

                    // Remove the resident from all of its other preferences' lists
                    Node<Hospital*>* removeHospital = cur->data->getHospitalPreferences()->getHead();
                    int level = 0;

                    while (removeHospital != nullptr) {
                        // Remove the resident from other hospitals lists
                        if (removeHospital->data->getName().compare(nextHospital->getName()) != 0) {
                            removeHospital->data->removeResident(cur->data, level);
                            std::cout << "Removed " << cur->data->getName() << " from " << removeHospital->data->getName() << std::endl;
                        }
                        level++;
                        removeHospital = removeHospital->next;
                    }

                    cur = cur->next;
                } else {
                    // The hospital is full, so have to remove the current resident
                    Resident* residentToRemove = cur->data;
                    cur = cur->next;

                    nextHospital->removeResident(residentToRemove, j);
                    residentToRemove->getHospitalPreferences()->remove(nextHospital);
                    std::cout << "Removed " << residentToRemove->getName() << " from " << nextHospital->getName() << std::endl;
                }
            }
        }

        for (int j = 0; j < Hospital::NUM_LEVELS; j++) {
            nextHospital->getAssignments()[j].printList();
        }
        std::cout << std::endl;
    }

    std::cout << "Finished algo" << std::endl << std::endl;

    // Print the final results
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

    delete [] mutableHospitals.arr;
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