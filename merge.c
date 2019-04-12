/*
Joseph Schwalb
CSCI 242
4/14/19
This program measures the merge sort time complexity.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array_util.h"
#include "file_util.h"

void main(){
  clock_t start_t, end_t, total_t, lap_t;
  size_t size = 10000;
  char *random_data = "random_data.txt";
  char *sorted_data = "sorted_data.txt";
  char *plot_data = "plot_data.txt";
  int *arr = (int*) calloc (5, sizeof(int));
  int clock_times[] = {0,0,0,0};
  int n_coef[] = {1,2,3,4};
  int idx, n, i;

  printf("Clock Start...\n");
  start_t = clock();
  for (n = 0; n < 4; n++){
    file_gen(random_data, n_coef[n]*size);
    arr = read_file(random_data, arr);

    MergeSort(arr, 0, size-1);
    write_file(sorted_data, arr);

    end_t = clock();
    lap_t = (end_t - start_t);
    total_t = total_t + lap_t;
    clock_times[n] = lap_t;
    printf("Lap clock cycles by CPU: %ld\n", lap_t);
  }
  printf("Total clock cycles by CPU: %ld\n", total_t);
  FILE *plt_data = fopen(plot_data, "w");
  FILE *nlogn_time = fopen("nlogn_time.txt", "w");
  for (i = 0; i < 4; i++){
    fprintf(plt_data, "%ld %d\n", size * n_coef[i], clock_times[i]);
    fprintf(nlogn_time, "%ld %f\n", size * n_coef[i], size * n_coef[i] * log10(n_coef[i]));
  }
  free(arr);

  //Plot the data
  FILE *gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set style line 1 linecolor \"red\"\n");
  fprintf(gp, "set style line 2 linecolor \"blue\"\n");

  fprintf(gp, "plot '-' linestyle 1 with linespoints title \"1,000,000 Clock Cycles/Sec\"\n");//, '-' with linespoints ls 2 title \"NlogN Time\"\n");
  for (i = 0; i < 4; i++)
    fprintf(gp, "%ld %d\n", size * n_coef[i], clock_times[i]); //array size <x-axis> vs clock cycles <y-axis>
  fprintf(gp, "e\n");

  fclose(gp);

}
