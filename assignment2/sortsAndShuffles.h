#pragma once

#include "util.h"

// Selection sort that returns the number of comparisons made
int selectionSort(StringArr* data);

// Insertion sort that returns the number of comparisons made
int insertionSort(StringArr* data);

// Merge sort that returns the number of comparisons made
int mergeSort(StringArr* data);

// Helper function for merge sort to make the calls in the main function consistent with the other sorts
// End is inclusive
int mergeSortWithIndices(StringArr* data, int start, int end);

// Helper function for merge sort to merge 2 halves of the subarray
int merge(StringArr* data, int start, int end, int mid);

// Quicksort function that returns the number of comparisons made
int quickSort(StringArr* data);

// Helper function for quicksort
int quickSortWithIndices(StringArr* data, int start, int end);

// Helper function to partition the array in quicksort
int* partition(StringArr* data, int start, int end, int pivotIndex);

// Knuth shuffle
void knuthShuffle(StringArr* data);