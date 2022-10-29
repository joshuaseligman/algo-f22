#include "hospital.h"
#include "resident.h"
#include "list.h"

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

Hospital::Hospital() {
    // Initialize leveledAssignments to be NUM_LEVELS of empty lists
    leveledAssignments = new List<Resident*>[NUM_LEVELS];

    numAssigned = 0;
}

Hospital::~Hospital() {
    delete [] assignments;
}

void Hospital::clearMemory() {
    delete [] leveledAssignments;
}

void Hospital::loadData(std::string data, int hospIndex, ResidentArr* residents) {
    assignments = new Resident*[residents->length];

    // The part of the line before the colon is the name
    int colonIndex = data.find(":");
    name = data.substr(0, colonIndex);

    // Set the index of the element (number in string - 1), but quicker to pass the index as is
    index = hospIndex;

    // Get the remainder of the string after the colon and the space
    std::string remainder = data.substr(colonIndex + 2, std::string::npos);

    // Ignore the space before the hyphen and save the capacity
    std::stringstream ss(remainder);
    ss >> capacity;
}

void Hospital::addResident(Resident* resident) {
    assignments[numAssigned] = resident;
    numAssigned++;
}

void Hospital::addResident(Resident* resident, int level) {
    // Create a node and add it to the level
    Node<Resident*>* residentNode = new Node<Resident*>(resident);
    leveledAssignments[level].priorityAdd(residentNode, level);
}

void Hospital::removeResident(Resident* resident, int level) {
    // Create a node and add it to the level
    leveledAssignments[level].remove(resident);
}

int Hospital::compare(Hospital* hospitalComp) {
    // Initialize the comparison to be equal to each other
    int out = 0;
    
    // Compute the difference between the number of provisionally assigned residents and the capacity
    int thisDiff = this->getNumAssigned() - this->getCapacity();
    int otherDiff = hospitalComp->getNumAssigned() - hospitalComp->getCapacity();

    if (thisDiff < otherDiff) {
        // This hospital is less than hospitalComp, so set out to -1
        out = -1;
    } else if (thisDiff > otherDiff) {
        // This hospital is greater than hospitalComp, so set out to 1
        out = 1;
    } else { // They both have the same number of provisionally assigned residents
        if (this->getCapacity() < hospitalComp->getCapacity()) {
            // This hospital is less than hospitalComp, so set out to -1
            out = -1;
        } else if (this->getCapacity() > hospitalComp->getCapacity()) {
            // This hospital is greater than hospitalComp, so set out to 1
            out = 1;
        }
    }

    // Return the result of the comparison
    return out;
}

bool Hospital::isFull() {
    return capacity <= getNumAssigned();
}

bool Hospital::isFullRange(int lastLevel) {
    return capacity <= getNumAssignedRange(lastLevel);
}

std::string Hospital::getName() {
    return name;
}

int Hospital::getIndex() {
    return index;
}

int Hospital::getCapacity() {
    return capacity;
}

int Hospital::getNumAssigned() {
    return numAssigned;
}

int Hospital::getNumAssignedRange(int lastLevel) {
    if (lastLevel >= Hospital::NUM_LEVELS) {
        throw std::invalid_argument("Invalid level. Must be less than " + std::to_string(Hospital::NUM_LEVELS));
        return -1;
    }
    int sum = 0;
    for (int i = 0; i <= lastLevel; i++) {
        sum += leveledAssignments[i].getSize();
    }
    return sum;
}

Resident** Hospital::getAssignments() {
    return assignments;
}

int Hospital::getFirstChoiceCount() {
    return firstChoice;
}

void Hospital::incrementFirstChoice() {
    firstChoice++;
}

void Hospital::printAssignments() {
    for (int i = 0; i < numAssigned; i++) {
        std::cout << assignments[i]->getName() << " ";
    }
    std::cout << std::endl;
}

void Hospital::sortResidentAssignments() {
    quickSortWithIndices(assignments, 0, numAssigned - 1);
}

void Hospital::quickSortWithIndices(Resident** data, int start, int end) {
    // Base case for arrays of size 1 or 0
    if (start >= end) {
        // No work is needed
        return;
    }

    // The variable used for the pivot index
    int pivotIndex;

    if (end - start < 3) {
        // Array of size 2 should take either element as it will need exactly 1 more divide regardless of the pivot
        pivotIndex = start;
    } else {
        // Generate 3 random indices that are all unique to use to pick a pivot
        int pivotChoice1 = rand() % (end - start) + start;
        int pivotChoice2 = rand() % (end - start) + start;
        while (pivotChoice2 != pivotChoice1) {
            pivotChoice2 = rand() % (end - start) + start;
        }
        int pivotChoice3 = rand() % (end - start) + start;
        while (pivotChoice3 != pivotChoice1 && pivotChoice3 != pivotChoice2) {
            pivotChoice3 = rand() % (end - start) + start;
        }

        // Find the median of the 3 indices picked and set the pivot index appropriately
        // This will hopefully create balanced partitions regardless of the status of the array
        if (data[pivotChoice1]->compare(data[pivotChoice2]) <= 0 && data[pivotChoice1]->compare(data[pivotChoice3]) >= 0) {
            pivotIndex = pivotChoice1;
        } else if (data[pivotChoice1]->compare(data[pivotChoice3]) <= 0 && data[pivotChoice1]->compare(data[pivotChoice2]) >= 0) {
            pivotIndex = pivotChoice1;
        } else if (data[pivotChoice2]->compare(data[pivotChoice1]) <= 0 && data[pivotChoice2]->compare(data[pivotChoice3]) >= 0) {
            pivotIndex = pivotChoice2;
        } else if (data[pivotChoice2]->compare(data[pivotChoice1]) >= 0 && data[pivotChoice2]->compare(data[pivotChoice3]) <= 0) {
            pivotIndex = pivotChoice2;
        } else {
            pivotIndex = pivotChoice3;
        }
    }

    // Partition the data around the pivot
    int partitionOut = partition(data, start, end, pivotIndex);

    // Sort each of the partitions
    quickSortWithIndices(data, start, partitionOut - 1);
    quickSortWithIndices(data, partitionOut + 1, end);
}

int Hospital::partition(Resident** data, int start, int end, int pivotIndex) {
    // Move the pivot to the end of the subarray
    Resident* pivot = data[pivotIndex];
    data[pivotIndex] = data[end];
    data[end] = pivot;

    // We initially do not have any items in the low partition, so make it less than the start
    int lastLowPartitonIndex = start - 1;

    // Iterate through the subarray, excluding the pivot
    for (int i = start; i <= end - 1; i++) {
        // Check if the element is less than the pivot
        if (data[i]->compare(pivot) < 0) {
            // We have an element for the low partition
            lastLowPartitonIndex++;

            // Move the element to the end of the low partition
            Resident* temp = data[i];
            data[i] = data[lastLowPartitonIndex];
            data[lastLowPartitonIndex] = temp;
        }
    }

    // Move the pivot into its appropriate place between the partitions
    data[end] = data[lastLowPartitonIndex + 1];
    data[lastLowPartitonIndex + 1] = pivot;

    return lastLowPartitonIndex + 1;
}