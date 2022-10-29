#include "stableMatching.h"
#include "resident.h"
#include "hospital.h"
#include "util.h"
#include "sort.h"
#include "list.h"

#include "stdlib.h"

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
                // The first number should be the number of residents
                ss >> numResidents;
            } else if (numHospitals == -1) {
                // The second number should be the number of hospitals
                ss >> numHospitals;
            } else {
                // The third number is the number of preferences each resident gets
                ss >> Hospital::NUM_LEVELS;
            }
        }
        ptr = strtok(NULL, " ");  
    }

    // Create default residents and hospitals with no preferences and no capacity
    ResidentArr* residents = createResidents(numResidents);
    HospitalArr* hospitals = createHospitals(numHospitals);

    for (int i = 0; i < residents->length; i++) {
        residents->arr[i].loadData(data->arr[i + 1], i, hospitals);
    }

    for (int i = 0; i < hospitals->length; i++) {
        hospitals->arr[i].loadData(data->arr[residents->length + 1 + i], i, residents);
    }
    
    // Linked list for the best possible output
    List<AlgoOutput*>* best = new List<AlgoOutput*>;

    // Get the best possible output in O(n!) time
    stableMatchRecursive(residents, hospitals, 0, best);

    // Print out the best possibilities
    Node<AlgoOutput*>* cur = best->getHead();
    while (cur != nullptr) {
        std::cout << cur->data->assignmentsString;
        std::cout << "Resident happiness: " << cur->data->residentHappiness << std::endl;
        std::cout << "Hospital happiness: " << cur->data->hospitalHappiness << std::endl << std::endl;

        cur = cur->next;
    }

    // Memory cleanup
    best->clear(true);
    delete best;

    // Reset all assignments to null
    for (int i = 0; i < residents->length; i++) {
        residents->arr[i].setAssignment(nullptr);
    }

    std::cout << "----- Actual algorithm -----" << std::endl;

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
        Hospital* cur = residents->arr[i].getHospitalPreferences()[residents->arr[i].getCurPreferenceIndex()];

        // Add each resident to their top choice hospital
        cur->addResident(&residents->arr[i]);
    }

    bool hasToCheck = true;

    while (hasToCheck) {
        List<Resident*> residentsToReassign;

        for (int i = 0; i < hospitals->length; i++) {
            while (hospitals->arr[i].getNumAssigned() - hospitals->arr[i].getCapacity() > 0) {
                hospitals->arr[i].sortResidentAssignments();
                hospitals->arr[i].printAssignments();

                Resident* residentToRemove = hospitals->arr[i].getAssignments()[hospitals->arr[i].getNumAssigned() - 1];

                Resident* swapRes = nullptr;
                int hospIndex = -1;

                for (int j = 0; j < residentToRemove->getCurPreferenceIndex(); j++) {
                    Hospital* checkHosp = residentToRemove->getHospitalPreferences()[j];
                    for (int k = 0; k < checkHosp->getNumAssigned(); k++) {
                        if (residentToRemove->compare(checkHosp->getAssignments()[k]) < 0) {
                            if (swapRes != nullptr) {
                                if (swapRes->compare(checkHosp->getAssignments()[k]) < 0) {
                                    swapRes = checkHosp->getAssignments()[k];
                                    hospIndex = j;
                                }
                            } else {
                                swapRes = checkHosp->getAssignments()[k];
                                hospIndex = j;
                            }
                        }
                    }
                }

                if (swapRes != nullptr) {
                    residentToRemove->getHospitalPreferences()[hospIndex]->replace(swapRes, residentToRemove);
                    residentToRemove->setCurPreferenceIndex(hospIndex);
                    residentToRemove = swapRes;
                }

                hospitals->arr[i].setNumAssigned(hospitals->arr[i].getNumAssigned() - 1);
                residentToRemove->setCurPreferenceIndex(residentToRemove->getCurPreferenceIndex() + 1);
                Node<Resident*>* resNode = new Node<Resident*>(residentToRemove);
                residentsToReassign.enqueue(resNode);             
            }
        }
        if (residentsToReassign.getSize() > 0) {
            Node<Resident*>* res = residentsToReassign.dequeue();

            if (res->data->getCurPreferenceIndex() < Hospital::NUM_LEVELS) {
                res->data->getHospitalPreferences()[res->data->getCurPreferenceIndex()]->addResident(res->data);
            }

            delete res;
        } else {
            hasToCheck = false;
        }
    }

    // Formally assign each resident to the hospitals
    for (int i = 0; i < hospitals->length; i++) {
        for (int j = 0; j < hospitals->arr[i].getNumAssigned(); j++) {
            hospitals->arr[i].getAssignments()[j]->setAssignment(&hospitals->arr[i]);
        }
    }

    std::cout << "Finished main algo" << std::endl << std::endl;

    // Print the final results
    std::cout << "Initial results:" << std::endl;
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

    std::cout << std::endl;

    // // Try to do swaps to boost the performance of the algorithm
    performSwaps(residents);

    // Print the final results
    std::cout << std::endl;
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

void stableMatchRecursive(ResidentArr* residents, HospitalArr* hospitals, int curResident, List<AlgoOutput*>* best) {
    // Each hospital assignment should be considered for each resident
    for (int i = 0; i <= hospitals->length; i++) {
        // Residents can also be unassigned
        if (i == hospitals->length) {
            residents->arr[curResident].setAssignment(nullptr);
        } else {
            // Assign the resident to the hospital
            residents->arr[curResident].setAssignment(&hospitals->arr[i]);
        }

        if (curResident < residents->length - 1) {
            // Get all permutations of the remaining residents
            stableMatchRecursive(residents, hospitals, curResident + 1, best);
        } else {
            // Assume stable at first
            bool stable = true;

            // Array to keep track of number of residents assigned to each hospital
            int assignmentCount[hospitals->length];
            for (int j = 0; j < hospitals->length; j++) {
                assignmentCount[j] = 0;
            }

            for (int j = 0; j < residents->length; j++) {
                if (residents->arr[j].getAssignment() != nullptr) {
                    // Check the assignment to the preference list
                    if (residents->arr[j].getPreferencesArr()[residents->arr[j].getAssignment()->getIndex()] > 0) {
                        // The hospital is a valid assignment
                        assignmentCount[residents->arr[j].getAssignment()->getIndex()]++;
                    } else {
                        // Invalid permutation
                        stable = false;
                        break;
                    }
                }
            }

            if (stable) {
                for (int k = 0; k < hospitals->length; k++) {
                    // Make sure all hospitals are at or under capacity
                    if (hospitals->arr[k].getCapacity() < assignmentCount[k]) {
                        stable = false;
                        break;
                    }
                }
            }

            if (stable) {
                // Compute the resident happiness score
                double residentHappiness = computeResidentHappiness(residents);
                if (best->isEmpty() || residentHappiness >= best->getHead()->data->residentHappiness) {
                    AlgoOutput* newOut = new AlgoOutput;
                    newOut->residentHappiness = residentHappiness;

                    // Update the best to be the new best score
                    std::stringstream ss;

                    // Generate the string for the output
                    for (int i = 0; i < residents->length; i++) {
                        if (residents->arr[i].getAssignment() != nullptr) {
                            ss << "(" << residents->arr[i].getName() << ", " << residents->arr[i].getAssignment()->getName() << ")\n";
                        } else {
                            ss << "(" << residents->arr[i].getName() << ", nullptr)\n";
                        }
                    }

                    // Assign the best node to have the new string
                    newOut->assignmentsString = ss.str();

                    // Compute the hospital happiness as an additional metric
                    double sum = 0;
                    for (int i = 0; i < hospitals->length; i++) {
                        sum += (double) assignmentCount[i] / hospitals->arr[i].getCapacity();
                    }
                    double hospitalHappiness = sum / hospitals->length;
                    newOut->hospitalHappiness = hospitalHappiness;

                    Node<AlgoOutput*>* newNode = new Node<AlgoOutput*>(newOut);

                    if (!best->isEmpty() && residentHappiness > best->getHead()->data->residentHappiness) {
                        best->clear(true);
                    }
                    best->enqueue(newNode);
                }
            }
        }
    }
}

void performSwaps(ResidentArr* residents) {
    // Make any needed adjustments to increase resident happiness
    bool swapped = true;
    while (swapped) {
        // Initialize the residents to swap to be nothing
        Resident* res1 = nullptr;
        Resident* res2 = nullptr;
        double bestDiff = 0;

        for (int i = 0; i < residents->length; i++) {
            for (int j = i + 1; j < residents->length; j++) {
                // Get the current assignments
                Hospital* iHosp = residents->arr[i].getAssignment();
                Hospital* jHosp = residents->arr[j].getAssignment();

                bool canSwap = true;
                // Make sure jHosp is a preference for resident i
                if (jHosp != nullptr && residents->arr[i].getPreferencesArr()[jHosp->getIndex()] == 0) {
                    // Cannot swap if resident i does not want to go to jHosp
                    canSwap = false;
                } else if (iHosp != nullptr && residents->arr[j].getPreferencesArr()[iHosp->getIndex()] == 0) {
                    // Same but for resident j and iHosp
                    canSwap = false;
                }

                if (canSwap) {
                    // Compute the current average happiness among the 2 residents
                    int iCurHappiness = 0;
                    if (iHosp != nullptr) {
                        iCurHappiness = residents->arr[i].getPreferencesArr()[iHosp->getIndex()];
                    }

                    int jCurHappiness = 0;
                    if (jHosp != nullptr) {
                        jCurHappiness = residents->arr[j].getPreferencesArr()[jHosp->getIndex()];
                    }
                    double curHappiness = (double) (iCurHappiness + jCurHappiness) / 2;

                    // Compute the average happiness if the 2 residents swapped
                    int iSwapHappiness = 0;
                    if (jHosp != nullptr) {
                        iSwapHappiness = residents->arr[i].getPreferencesArr()[jHosp->getIndex()];
                    }

                    int jSwapHappiness = 0;
                    if (iHosp != nullptr) {
                        jSwapHappiness = residents->arr[j].getPreferencesArr()[iHosp->getIndex()];
                    }
                    double swapHappiness = (double) (iSwapHappiness + jSwapHappiness) / 2;

                    // Make sure the new happiness is better than it was before
                    if (swapHappiness > curHappiness) {
                        // Get the gained happiness
                        double diff = swapHappiness - curHappiness;

                        // Check to see if it is better than the current best
                        if (diff > bestDiff) {
                            // Update the variables
                            bestDiff = diff;
                            res1 = &residents->arr[i];
                            res2 = &residents->arr[j];
                        } else if (diff == bestDiff && rand() % 2 == 0) {
                            // If equal, randomly pick one or the other to use as the best difference
                            bestDiff = diff;
                            res1 = &residents->arr[i];
                            res2 = &residents->arr[j];
                        }
                    }
                }
            }
        }

        // Make the swap if a possible swap was found
        if (res1 != nullptr && res2 != nullptr) {
            // Get the hospitals being used
            Hospital* h1 = res1->getAssignment();
            Hospital* h2 = res2->getAssignment();

            // Replace the residents
            h1->replace(res1, res2);
            h2->replace(res2, res1);

            // Update the assignments
            res2->setAssignment(h1);
            res1->setAssignment(h2);

            std::cout << "Swapped " << res1->getName() << " and " << res2->getName() << std::endl;
        } else {
            // No swaps were made, so can set the flag to false and end the loop
            std::cout << "No swaps made" << std::endl;
            swapped = false;
        }
    }
}