#include "fractionalKnapsack.h"
#include "util.h"
#include "spice.h"
#include "queue.h"
#include "node.h"
#include "sort.h"

#include <iostream>

void fractionalKnapsackAlgo(StringArr* data) {

    // Create a queue for each to preserve order.
    // Spice queue will be turned into an array after the file is read
    Queue<Spice*> spiceQueue;
    Queue<int> knapsacks;

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

            // Create the spice object
            Spice* newSpice = new Spice(name, price, quantity);

            // Add it to the queue
            Node<Spice*>* spiceNode = new Node(newSpice);
            spiceQueue.enqueue(spiceNode);
        } else if (data->arr[i].substr(0, 8).compare("knapsack") == 0) {
            // Knapsack data starts after the last space
            int startOfCapacity = data->arr[i].find_last_of(" ") + 1;

            // The last character will be a semicolon, so can exclude that character
            std::string capacityStr = data->arr[i].substr(startOfCapacity, data->arr[i].length() - 1 - startOfCapacity);

            // Do the type conversion
            int knapsackCapacity = std::stoi(capacityStr);
            Node<int>* knapsackNode = new Node<int>(knapsackCapacity);
            knapsacks.enqueue(knapsackNode);
        }
    }

    // Create the struct
    SpiceArr spiceArr;
    // The array is the same size as the queue
    spiceArr.arr = new Spice*[spiceQueue.getSize()];
    spiceArr.length = spiceQueue.getSize();

    // Iterate through the created spice objects
    for (int i = 0; i < spiceArr.length; i++) {
        Node<Spice*>* spiceNode = spiceQueue.dequeue();
        // Store the object pointer in the array
        spiceArr.arr[i] = spiceNode->data;

        // Memory management
        delete spiceNode;
    }

    // Run the algorithm with the given spices and knapsacks
    runAlgo(&spiceArr, &knapsacks);

    // Memory management
    for (int i = 0; i < spiceArr.length; i++) {
        delete spiceArr.arr[i];
    }
    delete [] spiceArr.arr;
}

void runAlgo(SpiceArr* spices, Queue<int>* knapsacks) {
    // Start off by running a sort on the spices array to make them in descending order
    quickSort(spices);

    while (!knapsacks->isEmpty()) {
        Node<int>* curKnapsack = knapsacks->dequeue();

        // Create an array that corresponds with the spice array for keeping track of what was taken by the knapsack
        int quantityTaken[spices->length];
        for (int i = 0; i < spices->length; i++) {
            quantityTaken[i] = 0;
        }

        // Start off with an empty knapsack and a value of 0
        int capacityLeft = curKnapsack->data;
        double spiceValue = 0;

        // Start considering the first element in the array (most valuable per unit)
        int spiceIndex = 0;

        // Continue until the knapsack is full or until there is no more spice to take
        while (capacityLeft > 0 && spiceIndex < spices->length) {
            // If there is space for the entire pile of spice, take it all
            if (capacityLeft >= spices->arr[spiceIndex]->getQuantity()) {
                // Update the array of spice taken
                quantityTaken[spiceIndex] = spices->arr[spiceIndex]->getQuantity();

                // Be greedy and take everything available if possible
                capacityLeft -= spices->arr[spiceIndex]->getQuantity();
                spiceValue += spices->arr[spiceIndex]->getPrice();
            } else {
                // Update the table entry
                quantityTaken[spiceIndex] = capacityLeft;

                // Compute the value of the spice we can take
                spiceValue += capacityLeft * spices->arr[spiceIndex]->getUnitPrice();

                // Update the capacity to be 0
                capacityLeft = 0;
            }
            // Go on to the next spice
            spiceIndex++;
        }

        // Start with this text
        std::cout << "Knapsack of capacity " << curKnapsack->data << " is worth " << spiceValue << " quatloos and contains";

        // Iterate through all of the spices
        for (int j = 0; j < spices->length; j++) {
            // Only print out the spices we take
            if (quantityTaken[j] > 0) {
                // Little formatting logic
                if (j > 0) {
                    std::cout << ", ";
                } else {
                    std::cout << " ";
                }
                // The amount and name of the spice taken
                std::cout << quantityTaken[j] << " scoops of " << spices->arr[j]->getName();
            }
        }
        std::cout << "." << std::endl;

        // Memory management
        delete curKnapsack;
    }
}