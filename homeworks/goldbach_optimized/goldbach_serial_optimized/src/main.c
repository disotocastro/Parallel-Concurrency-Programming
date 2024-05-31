#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "file_read_out.h"
#include "array_numbers.h"
#include "goldbach.h"

int main(int argc, char* argv[]) {
  analyze_arguments(argc, argv);

  FILE* input = stdin;
  array_numbers_t* arr_input_stdin = (array_numbers_t*)
    calloc(1, sizeof(array_numbers_t));
  array_init(arr_input_stdin);
  read_file(input, arr_input_stdin);

  int64_t largest_element = largest_element_arr(arr_input_stdin);
  array_numbers_t* arr_prime_num = (array_numbers_t*)
    calloc(1, sizeof(array_numbers_t));
  array_init(arr_prime_num);
  trial_division(arr_prime_num, largest_element);

  struct timespec start_time;
  clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);

  goldbach(arr_input_stdin, arr_prime_num);

  struct timespec finish_time;
  clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);

  double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
    (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
  printf("execution time: %.9lfs\n", elapsed);

  array_destroy(arr_prime_num);
  array_destroy(arr_input_stdin);
  free(arr_prime_num);
  free(arr_input_stdin);
  return EXIT_SUCCESS;
}
