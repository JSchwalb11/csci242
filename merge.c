/*
Joseph Schwalb
CSCI 242
4/14/19
This program measures the merge sort time complexity.
*/

#include <time.h>
#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include "array_util.h"
#include "file_util.h"

void main(){
  clock_t start_t, end_t, total_t, lap_t;
  size_t size = 10000;
  char *random_data = "random_data.txt";
  char *sorted_data = "sorted_data.txt";
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
  free(arr);

  //Plot the data
  FILE *gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set style line 1 linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 pointtype 7 pointsize 1.5\n");
  fprintf(gp, "set title 'Array Size vs Clock Cycles'\n");
  fprintf(gp, "set label 1 \"1,000,000 Clock Cycles / Sec\"\n");
  fprintf(gp, "set label 1 at graph 0.02, 0.85 tc lt 3\n");

  fprintf(gp, "set ylabel \"Clock Cycles\"\n");
  fprintf(gp, "set xlabel \"Array Size\"\n");
  //fprintf(gp, "set output 'Assignment3.pdf'\n");
  fprintf(gp, "plot '-' with linespoints linestyle 1\n");
  for (i = 0; i < 4; i++)
    fprintf(gp, "%ld %d\n", size * n_coef[i], clock_times[i]); //array size <x-axis> vs clock cycles <y-axis>
  fprintf(gp, "e\n");
  fclose(gp);

}
