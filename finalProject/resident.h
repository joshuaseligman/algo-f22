#pragma once

#include <string>

#include "list.h"
#include "util.h"

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
    private:
        // The name for printing the output
        std::string name;

        // Index for referencing the resident from an array
        int index;

        // List of initial preferences
        List<Hospital*>* hospitalPreferences;

        // Add the preferences to the list
        void addPreferences(std::string preferences, HospitalArr* hospitals);
};