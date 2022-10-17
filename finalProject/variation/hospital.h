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

        // Returns if the hospital is full or not
        bool isFull();

        // Replaces the lowest preferred resident with a new resident
        void replaceLowest(Resident* newResident);

        // Adds the resident to the hospital
        void addResident(Resident* newResident);
        
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
        int getLowestPreferredAssignedResidentIndex();

        // Setter for the lowest preferred assigned resident index
        void setLowestPreferredAssignedResidentIndex();
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

        // The index of the loweset preferred resident currently assigned to the hospital
        int lowestPreferredAssignedResidentIndex;

        // Add the preferences to the list
        void addPreferences(std::string preferences, ResidentArr* residents);
};

// Struct for working with hospitals on the heap
struct HospitalArr {
    Hospital* arr;
    int length;
};