#pragma once

#include "util.h"
#include "spice.h"
#include "queue.h"

// The main function to call that reads in the data and calls the run function
void fractionalKnapsackAlgo(StringArr* data);

// Contains the formal implementation of the fractional knapsack algorithm
void runAlgo(SpiceArr* spices, Queue<int>* knapsacks);