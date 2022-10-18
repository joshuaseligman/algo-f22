#include "stableMatching.h"
#include "resident.h"
#include "hospital.h"
#include "util.h"

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
    }

    // Call the actual algorithm
    // generateStableMatches(residents, hospitals);

    // Memory management and clean up
    delete [] residents->arr;
    delete residents;

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
    // List<Resident*> residentList;

    // // Add the residents to a List for determining the next resident to propose
    // for (int i = 0; i < residents->length; i++) {
    //     Node<Resident*>* n = new Node(&residents->arr[i]);
    //     residentList.enqueue(n);
    // }

    // std::cout << std::endl;

    // while (!residentList.isEmpty()) {
    //     residentList.printList();

    //     Node<Resident*>* resident = residentList.dequeue();

    //     while (resident->data->getAssignment() == nullptr && !resident->data->getHospitalPreferences()->isEmpty()) {
    //         for (int j = 0; j < hospitals->length; j++) {
    //             std::cout << resident->data->getPreferencesArr()[j] << " ";
    //         }
    //         std::cout << std::endl;

    //         // Get the hospital at the front of the preference list
    //         Node<Hospital*>* preference = resident->data->getHospitalPreferences()->dequeue();

    //         // The hospital is full with more preferable residents, so the current resident is not getting in
    //         if (resident->data->getPreferencesArr()[preference->data->getIndex()] == 0) {
    //             // Clean up memory and try the next hospital
    //             delete preference;
    //             continue;
    //         }

    //         if (preference->data->isFull()) {
    //             // Get the lowest preferred assigned resident index
    //             preference->data->setLowestPreferredAssignedResidentIndex();

    //             // If the hospital is full, then replace the lowest preferred resident with the current resident
    //             Resident* lowest = &residents->arr[preference->data->getAssignedResidents()[preference->data->getLowestPreferredAssignedResidentIndex()].getIndex()];
    //             lowest->setAssignment(nullptr);

    //             preference->data->replaceLowest(resident->data);
    //             // Since the lowest preferred resident was replaced, we need to come back to it later
    //             residentList.enqueue(new Node<Resident*>(lowest));
    //         } else {
    //             // Add the new resident to the 
    //             preference->data->addResident(resident->data);
    //         }

    //         // Print the assignment as it happens
    //         std::cout << "Assigned " << resident->data->getName() << " to " << resident->data->getAssignment()->getName() << std::endl;

    //         if (preference->data->isFull()) {
    //             // Get the lowest preferred assigned resident index
    //             preference->data->setLowestPreferredAssignedResidentIndex();

    //             // We need to iterate through all of the residents
    //             for (int i = 0; i < residents->length; i++) {
    //                 // Check if the current resident is less preferred compared to the lowest preferred resident
    //                 if (preference->data->getResidentPreferences()[residents->arr[i].getIndex()] > preference->data->getResidentPreferences()[preference->data->getAssignedResidents()[preference->data->getLowestPreferredAssignedResidentIndex()].getIndex()]) {

    //                     // Take the resident out of the running if that is the case
    //                     residents->arr[i].getPreferencesArr()[preference->data->getIndex()] = 0;
    //                     preference->data->getResidentPreferences()[residents->arr[i].getIndex()] = INT_MAX;
    //                 }
    //             }
    //         }

    //         // Clean up memory because the node is no longer needed
    //         delete preference;
    //     }

    //     // The resident is done for now and a new node has already been created if needed
    //     delete resident;
    // }

    // std::cout << "Finished algo" << std::endl << std::endl;

    // // Print the final results
    // std::cout << "Final results:" << std::endl;
    // for (int i = 0; i < residents->length; i++) {
    //     if (residents->arr[i].getAssignment() != nullptr) {
    //         std::cout << "(" << residents->arr[i].getName() << ", " << residents->arr[i].getAssignment()->getName() << ")" << std::endl;
    //     } else {
    //         std::cout << "(" << residents->arr[i].getName() << ", nullptr)" << std::endl;
    //     }
    // }
}