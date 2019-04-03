/*
Joseph Schwalb
CSCI 242
4/14/19
This program measures the merge sort time complexity.
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gnuplot.h>

int* resize(int* arr, int idx){
  //free one object
  int *tmp;
  tmp = (int*) calloc (5*((idx/5)+1), sizeof(int));
  memcpy(tmp, arr, (idx*sizeof(int)));
  free(arr); // free++
  return tmp;
}

void file_gen(char *p_filename, size_t size){
  time_t t = time(NULL);
  srand((unsigned) time(&t));
  int idx = 0;
  int *rand_int = (int*) calloc (1, sizeof(int));
  FILE *p_file = fopen(p_filename, "w");
  if (!p_file){
    printf("!p_file\n");
    exit(1);
  }
  for (idx = 0; idx < size; idx++){
    *rand_int = rand();// % (10000 - 1) + 1;
    fprintf(p_file, "%d\n", *rand_int);
  }
  free(rand_int);
  fclose(p_file);
}

int* read_file(char *p_filename, int* arr){
  int i = 0;
  char buff[32], *tok;
  FILE *p_file = fopen(p_filename, "r");

  for (i = 0; fgets(buff, sizeof(buff), p_file) != NULL; i++){
    tok = strtok(buff, "\n");
    arr = resize(arr, i);
    *(arr+i) = atoi(tok);
  }
  fclose(p_file);
  return arr;
}

void write_file(char* p_filename, int* arr){
  int i;
  FILE *p_file = fopen(p_filename, "w");

  for (i = 0; *(arr+i) != NULL; i++){
    fprintf(p_file, "%d\n", *(arr+i));
  }
  fclose(p_file);
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

MergeSort(int *arr, int i, int k) {
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

void main(){
  clock_t start_t;
  clock_t end_t;
  clock_t total_t;
  size_t size = 10000;
  char *random_data = "random_data.txt";
  char *sorted_data = "sorted_data.txt";
  int *arr = (int*) calloc (5, sizeof(int));
  int idx;

  printf("Clock Start...\n");
  start_t = clock();

  file_gen(random_data, size);
  arr = read_file(random_data, arr);
  MergeSort(arr, 0, size-1);
  write_file(sorted_data, arr);

  end_t = clock();
  printf("Clock End...\n");
  total_t = (double) (start_t - end_t) / CLOCKS_PER_SEC;
  //printf("Total time taken by CPU: %ld\n", total_t);

  free(arr);
  
  char *commands_for_gnuplot = "

  return;


}
