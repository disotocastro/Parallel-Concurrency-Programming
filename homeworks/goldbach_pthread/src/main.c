#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "file_read_out.h"
#include "array_numbers.h"
#include "goldbach.h"
#include "concurrency.h"

int main(int argc, char* argv[]) {
  FILE* input = stdin;
  int error = EXIT_SUCCESS;
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));

  if (shared_data) {
    analyze_arguments(argc, argv);
    shared_data->thread_count = get_thread_count(argc, argv);

    array_init(&shared_data->arr_input);
    read_file(input, &shared_data->arr_input);
    int64_t largest_element = largest_element_arr(&shared_data->arr_input);
    array_init(&shared_data->arr_prime_num);
    trial_division(&shared_data->arr_prime_num, largest_element);
    shared_data->can_print = (sem_t*) calloc
                                (shared_data->arr_input.count, sizeof(sem_t));

    if (shared_data->can_print) {
      struct timespec start_time;
      clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);

      error = create_threads(shared_data);

      struct timespec finish_time;
      clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);

      double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
        (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
      printf("execution time: %.9lfs\n", elapsed);

      free(shared_data->can_print);
    } else {
        fprintf(stderr, "Error: Could not allocate semaphores\n");
        error = EXIT_FAILURE;
    }

    array_destroy(&shared_data->arr_prime_num);
    array_destroy(&shared_data->arr_input);
    free(shared_data);
  } else {
      fprintf(stderr, "Error: Could not create dynamic memory\n");
      error = EXIT_FAILURE;
  }
  return error;
}
