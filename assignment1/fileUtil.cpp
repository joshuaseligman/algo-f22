#include <string>
#include <fstream>
#include <iostream>

#include "fileUtil.h"

void readFile(std::string filePath) {
    // File reading code from https://cplusplus.com/doc/tutorial/files/

    std::string line;
    std::ifstream file(filePath);
    if (file.is_open()) {
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open file " << filePath << std::endl;
    }
}