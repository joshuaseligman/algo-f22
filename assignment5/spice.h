#pragma once

#include <string>

class Spice {
    public:
        // Constructor for a spice object
        Spice(std::string spiceName, double spicePrice, int spiceQuantity);

        // Getters for the different fields
        std::string getName();
        double getPrice();
        int getQuantity();
        double getUnitPrice();

    private:
        // Name of the spice object
        std::string name;

        // Price of the spice object
        double price;

        // Quantity of the spice
        int quantity;

        // The unit price (price / quantity)
        double unitPrice;
};