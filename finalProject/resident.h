#pragma once

#include <string>

#include "list.h"
#include "util.h"

class Resident {
    public:
        // A static variable to keep track of the number of residents made so far
        inline static int index = 1;

        // Constructor
        Resident();

        ~Resident();

        // Add the preferences to the list
        void addPreferences(std::string preferences, HospitalArr* hospitals);

        // Getter for the name
        std::string getName();

        // Getter for the preferences
        List<Hospital*>* getHospitalPreferences();
    private:
        // The name for printing the output
        std::string name;

        List<Hospital*>* hospitalPreferences;
};