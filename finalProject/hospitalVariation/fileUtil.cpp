#include <string>
#include <fstream>
#include <iostream>

#include "fileUtil.h"
#include "util.h"

StringArr* readFile(std::string filePath) {
    // File reading code from https://cplusplus.com/doc/tutorial/files/

    // We need to determine how many items there are, so a counter would work well
    int numItems = 0;

    // Create the string buffer for storing each line
    std::string line;
    // Attempt to open the file
    std::ifstream file(filePath);
    if (file.is_open()) {
        // Read each line from the file
        while (getline(file, line)) {
            // Ignore empty lines
            if (!line.empty() && line.substr(0, 2).compare("--") != 0) {
                // During the first read through, we only need to count the number of lines
                // because we do not know how big to make the array
                numItems++;
            }
        }

        // Create the struct to output the data
        StringArr* outArr = new StringArr;
        outArr->arr = new std::string[numItems];
        outArr->length = numItems;

        // We will now reread the file and store the data now that the array has been
        // created with the correct size. Thus, we have to clear any error flags
        // and fix the pointer to go back to the top of the file 
        file.clear();
        file.seekg(0);

        // i is a counter to keep track of the index we are on when reading from the file
        int i = 0;
        while (getline(file, line)) {
            if (!line.empty() && line.substr(0, 2).compare("--") != 0) {
                // During the second read through, we will store the contents of the line in the array
                outArr->arr[i] = line;
                i++;
            }
        }

        // Close the file when done for safety
        file.close();

        return outArr;
    } else {
        // Throw an error if the file was not found
        throw std::invalid_argument("Unable to open file " + filePath);
    }
}