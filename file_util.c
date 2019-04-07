#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "array_util.h"

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

  for (i = 0; *(arr+i); i++){
    fprintf(p_file, "%d\n", *(arr+i));
  }
  fclose(p_file);
}
