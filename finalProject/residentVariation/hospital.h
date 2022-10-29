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

        // Determines if a hospital is full up to a certain level
        bool isFullRange(int lastLevel);
        
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

        // Constant for the number of preferences each resident gets. Determined at file read time
        inline static int NUM_LEVELS = 0;

        // Adds a resident to the given level
        void addResident(Resident* resident, int level);

        // Adds a resident to the hospital assignments
        void addResident(Resident* resident);

        // Removes a resident from the given level
        void removeResident(Resident* resident, int level);

        // Compares 2 hospitals based on the number of residents provisionally assigned to them and their respective capacities
        int compare(Hospital* hospitalComp);

        // Clears memory to make sure that the destructor doesn't tamper with the data when not wanted
        void clearMemory();

        // Getter for the number of residents that have this hosiptal as their first choice
        int getFirstChoiceCount();

        // Adds 1 to the first choice variable
        void incrementFirstChoice();

        void printAssignments();
    private:
        // The name for printing the output
        std::string name;

        // The index of the hospital for array references
        int index;

        // The capacity of the hospital
        int capacity;

        // Number of residents assigned to the hospital
        int numAssigned;

        // The currently assigned residents
        Resident** assignments;

        // Array for each level of assigned residents
        List<Resident*>* leveledAssignments;

        // The number of residents that want the hospital as its first choice
        int firstChoice;
};

// Struct for working with hospitals on the heap
struct HospitalArr {
    Hospital* arr;
    int length;
};