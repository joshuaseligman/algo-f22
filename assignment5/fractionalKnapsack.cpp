#include "fractionalKnapsack.h"
#include "util.h"

#include <iostream>

void fractionalKnapsackAlgo(StringArr* data) {

    // Go through the data file
    for (int i = 0; i < data->length; i++) {
        // Check to see if we are making a spice object or storing knapsack data
        if (data->arr[i].substr(0, 5).compare("spice") == 0) {
            // We will split by semicolons because they separate the fields
            char* ptr;
            ptr = strtok(data->arr[i].data(), ";");

            // All spice objects will have a name, price, and quantity
            std::string name;
            double price;
            int quantity;

            // Keep track of the position we are in within the line of the file
            int numIterations = 0;

            while (ptr != NULL) {
                std::string value(ptr);

                // Data we want starts after the last space and goes up to the semicolon that we split on
                value = value.substr(value.find_last_of(" ") + 1, std::string::npos);

                if (numIterations == 0) {
                    // First value is the name
                    name = value;
                } else if (numIterations == 1) {
                    // Second value is the price
                    price = std::stod(value);
                } else if (numIterations == 2) {
                    // Third value is the quantity
                    quantity = std::stoi(value);
                }

                // Move on to the next value to store
                numIterations++;
                ptr = strtok(NULL, ";");
            }

            std::cout << "Read a spice object: name = " << name << "; price = " << price << "; quantity = " << quantity << std::endl;
        } else if (data->arr[i].substr(0, 8).compare("knapsack") == 0) {
            // Knapsack data starts after the last space
            int startOfCapacity = data->arr[i].find_last_of(" ") + 1;

            // The last character will be a semicolon, so can exclude that character
            std::string capacityStr = data->arr[i].substr(startOfCapacity, data->arr[i].length() - 1 - startOfCapacity);

            // Do the type conversion
            int knapsackCapacity = std::stoi(capacityStr);
            std::cout << "Read a knapsack: capacity = " << knapsackCapacity << std::endl;
        }
    }
}