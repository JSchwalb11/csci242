#include <string.h>
#include <stdlib.h>

int* resize(int* arr, int idx){
  //free one object
  int *tmp;
  tmp = (int*) calloc (5*((idx/5)+1), sizeof(int));
  memcpy(tmp, arr, (idx*sizeof(int)));
  free(arr); // free++
  return tmp;
}

void Merge(int *arr, int i, int j, int k) {
  int mergedSize = k - i + 1;                // Size of merged partition
  int mergePos = 0;                          // Position to insert merged number
  int leftPos = 0;                           // Position of elements in left partition
  int rightPos = 0;                          // Position of elements in right partition
  int *mergedNumbers = (int*) calloc (mergedSize, sizeof(int));   // Dynamically allocates temporary array
                                         // for merged numbers

  leftPos = i;                           // Initialize left partition position
  rightPos = j + 1;                      // Initialize right partition position

  // Add smallest element from left or right partition to merged numbers
  while (leftPos <= j && rightPos <= k) {
    if (*(arr+leftPos) <= *(arr+rightPos)) {
       *(mergedNumbers+mergePos) = *(arr+leftPos);
       leftPos++;
    }
    else {
       *(mergedNumbers+mergePos) = *(arr+rightPos);
       rightPos++;

     }
    mergePos++;
  }

  // If left partition is not empty, add remaining elements to merged numbers
  while (leftPos <= j) {
    *(mergedNumbers+mergePos) = *(arr+leftPos);
    leftPos++;
    mergePos++;
  }

  // If right partition is not empty, add remaining elements to merged numbers
  while (rightPos <= k) {
    *(mergedNumbers+mergePos) = *(arr+rightPos);
    rightPos++;
    mergePos++;
  }

  // Copy merge number back to numbers
  for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
    *(arr+ i + mergePos) = *(mergedNumbers+mergePos);

  }
  free(mergedNumbers);
}

void MergeSort(int *arr, int i, int k) {
  int j = 0;

  if (i < k) {
     j = (i + k) / 2;  // Find the midpoint in the partition

     // Recursively sort left and right partitions
     MergeSort(arr, i, j);
     MergeSort(arr, j + 1, k);

     // Merge left and right partition in sorted order
     Merge(arr, i, j, k);
  }
}
