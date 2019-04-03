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

int* resize(int* arr, int idx){
  //free one object
  int *tmp;
  tmp = (int*) calloc (5*((idx/5)+1), sizeof(int));
  memcpy(tmp, arr, (idx*sizeof(int)));
  free(arr); // free++
  return tmp;
}

void file_gen(char *p_filename){
  time_t t = time(NULL);
  srand((unsigned) time(&t));
  int idx = 0;
  int *rand_int = (int*) calloc (1, sizeof(int));
  FILE *p_file = fopen(p_filename, "w");
  if (!p_file){
    printf("!p_file\n");
    exit(1);
  }
  for (idx = 0; idx < 10000; idx++){
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



void main(){
  clock_t start_t;
  clock_t end_t;
  clock_t total_t;
  char *filename = "data.txt";
  int *arr = (int*) calloc (5, sizeof(int));
  //printf("Starting of the program, start_t = %ld\n", start_t);
  file_gen(filename);
  arr = read_file(filename, arr);
  printf("Clock Start...\n");
  start_t = clock();
  /*
  merge_sort here;
  */
  end_t = clock();
  total_t = (double) (start_t - end_t) / CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %ld\n", total_t);
  /*
  */
  /*
  end_t = clock();
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %f\n", total_t  );
  printf("Exiting of the program...\n");
  */

  free(arr);
  return;


}
