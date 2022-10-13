#pragma once

#include <string>

#include "queue.h"
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
        Queue<Hospital*>* getHospitalPreferences();

        // Getter for the preferences array
        bool* getPreferencesArr();
    private:
        // The name for printing the output
        std::string name;

        // Index for referencing the resident from an array
        int index;

        // Queue of initial preferences
        Queue<Hospital*>* hospitalPreferences;

        // Boolean array to determine which hospitals are still in the running for the resident
        bool* preferenceArr;

        // Add the preferences to the list
        void addPreferences(std::string preferences, HospitalArr* hospitals);
};