#pragma once

#include <string>

class Hospital {
    public:
        // A static variable to keep track of the number of hospitals made so far
        inline static int index = 1;

        // Constructor
        Hospital();

        // Getter for the name
        std::string getName();
    private:
        // The name for printing the output
        std::string name;
};