#pragma once

#include <string>

#include "list.h"

class Hospital;
struct HospitalArr;

class Resident {
    public:
        // Constructor takes in all the data for each resident
        Resident();

        // Destructor makes sure heap elements are removed
        ~Resident();

        // Loads all the data to the resident
        void loadData(std::string data, int resIndex, HospitalArr* hospitals);

        // Getter for the index
        int getIndex();

        // Getter for the name
        std::string getName();

        // Getter for the preferences
        List<Hospital*>* getHospitalPreferences();

        // Getter for the preferences array
        int* getPreferencesArr();

        // Getter for the assignment
        Hospital* getAssignment();

        // Setter for the assignment
        void setAssignment(Hospital* newAssignment);
    private:
        // The name for printing the output
        std::string name;

        // Index for referencing the resident from an array
        int index;

        // List of initial preferences
        List<Hospital*>* hospitalPreferences;

        // Integer array to put the hospital rankings easily
        int* preferenceArr;

        // The hospital the resident is assigned to
        Hospital* assignment;

        // Add the preferences to the list
        void addPreferences(std::string preferences, HospitalArr* hospitals);
};

// Struct for creating an array of residents on the heap
struct ResidentArr {
    Resident* arr;
    int length;
};