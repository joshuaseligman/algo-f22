#pragma once

#include "util.h"

// Function that creates default residents with no connections to hospitals
ResidentArr* createResidents(int numResidents);

// Function that creates default hospitals with no connections to residents
HospitalArr* createHospitals(int numHospitals);