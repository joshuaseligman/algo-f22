#include "spice.h"
#include <string>

Spice::Spice(std::string spiceName, double spicePrice, int spiceQuantity) {
    // Each of these variables are provided in the constructor arguments
    name = spiceName;
    price = spicePrice;
    quantity = spiceQuantity;

    // Compute the unit price and store it
    unitPrice = price / quantity;
}

std::string Spice::getName() {
    return name;
}


double Spice::getPrice() {
    return price;
}

int Spice::getQuantity() {
    return quantity;
}


double Spice::getUnitPrice() {
    return unitPrice;
}