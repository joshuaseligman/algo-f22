#pragma once

#include "util.h"

// Selection sort that returns the number of comparisons made
void selectionSort(StringArr* data, int* comparisons = nullptr);

// Insertion sort that returns the number of comparisons made
void insertionSort(StringArr* data, int* comparisons = nullptr);

// Merge sort that returns the number of comparisons made
void mergeSort(StringArr* data, int* comparisons = nullptr);

// Helper function for merge sort to make the calls in the main function consistent with the other sorts
// End is inclusive
void mergeSortWithIndices(StringArr* data, int start, int end, int* comparisons);

// Helper function for merge sort to merge 2 halves of the subarray
void merge(StringArr* data, int start, int end, int mid, int* comparisons);

// Quicksort function that returns the number of comparisons made
void quickSort(StringArr* data, int* comparisons = nullptr);

// Helper function for quicksort
void quickSortWithIndices(StringArr* data, int start, int end, int* comparisons);

// Helper function to partition the array in quicksort
int partition(StringArr* data, int start, int end, int pivotIndex, int* comparisons);

// Knuth shuffle
void knuthShuffle(StringArr* data);