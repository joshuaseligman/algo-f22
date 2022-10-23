#pragma once

#include "list.h"

#include <string>

class Resident;
struct ResidentArr;

class Hospital {
    public:
        // Constructor for the hospital
        Hospital();

        // Destructor for the hospital
        ~Hospital();

        // Loads all the data to the hospital
        void loadData(std::string data, int hospIndex, ResidentArr* residents);

        // Returns if the hospital is full or not
        bool isFull();
        
        // Getter for the name
        std::string getName();

        // Getter for the hospital index
        int getIndex();

        // Getter for the capacity of the hospital
        int getCapacity();

        // Getter for the number of assigned residents
        int getNumAssigned();

        // Gets the number of residents assigned in the first n levels
        int getNumAssignedRange(int lastLevel);

        // Getter for the assignments
        List<Resident*>* getAssignments();

        // Constant for 3 levels (each resident gets 3 preferences as well)
        inline static const int NUM_LEVELS = 3;

        // Adds a resident to the given level
        void addResident(Resident* resident, int level);

        // Removes a resident from the given level
        void removeResident(Resident* resident, int level);

        // Compares 2 hospitals based on the number of residents provisionally assigned to them and their respective capacities
        int compare(Hospital* hospitalComp);

        // Clears memory to make sure that the destructor doesn't tamper with the data when not wanted
        void clearMemory();

        // Getter for the priority
        int getPriority();

        // Setter for the priority
        void setPriority(int newPriority);
    private:
        // The name for printing the output
        std::string name;

        // The index of the hospital for array references
        int index;

        // The capacity of the hospital
        int capacity;

        // Number of residents assigned to the hospital
        int numAssigned;

        // Array for each level of assigned residents
        List<Resident*>* leveledAssignments;

        // The priority for the hospital
        int priority;
};

// Struct for working with hospitals on the heap
struct HospitalArr {
    Hospital* arr;
    int length;
};