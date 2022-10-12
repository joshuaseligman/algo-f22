#pragma once

#include <string>

class Resident {
    public:
        // A static variable to keep track of the number of residents made so far
        inline static int index = 1;

        // Constructor
        Resident();

        // Getter for the name
        std::string getName();
    private:
        // The name for printing the output
        std::string name;
};