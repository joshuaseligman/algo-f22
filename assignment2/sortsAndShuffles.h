#pragma once

#include "util.h"

// Selection sort that returns the number of comparisons made
int selectionSort(StringArr* data);

// Insertion sort that returns the number of comparisons made
int insertionSort(StringArr* data);

// Knuth shuffle
void knuthShuffle(StringArr* data);