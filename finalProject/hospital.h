#pragma once

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
        
        // Getter for the name
        std::string getName();

        // Getter for the hospital index
        int getIndex();

        // Getter for the capacity of the hospital
        int getCapacity();

        // Getter for the number of assigned residents
        int getNumAssigned();

        // Getter for the array of preferences for the hospital
        int* getResidentPreferences();

        // Getter for the array of the residents provisionally assigned to the hospital
        Resident* getAssignedResidents();

        // Getter for the loweset preferred resident currently assigned to the hospital
        Resident* getLowestPreferredAssignedResident();
    private:
        // The name for printing the output
        std::string name;

        // The index of the hospital for array references
        int index;

        // The capacity of the hospital
        int capacity;

        // Number of residents already assigned to the hospital
        int numAssigned;

        // Array of preferences for the hospital
        int* residentPreferences;

        // Array of the residents provisionally assigned to the hospital
        Resident* assignedResidents;

        // The loweset preferred resident currently assigned to the hospital
        Resident* lowestPreferredAssignedResident;

        // Add the preferences to the list
        void addPreferences(std::string preferences, ResidentArr* residents);
};

// Struct for working with hospitals on the heap
struct HospitalArr {
    Hospital* arr;
    int length;
};