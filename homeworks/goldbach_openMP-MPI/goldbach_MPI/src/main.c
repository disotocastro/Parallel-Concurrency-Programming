// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include <inttypes.h>
#include <mpi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "array_numbers.h"
#include "file_read_out.h"
#include "goldbach.h"

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int rank = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int process_count = -1;
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);

  char hostname[MPI_MAX_PROCESSOR_NAME];
  int hostname_length = -1;
  MPI_Get_processor_name(hostname, &hostname_length);

  // Se empieza a tomar el tiempo
  struct timespec start_time;
  clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &start_time);

  analyze_arguments(argc, argv);

  FILE* input = stdin;
  array_numbers_t* arr_input_stdin =
      (array_numbers_t*)calloc(1, sizeof(array_numbers_t));
  array_init(arr_input_stdin);

  int total_input_num = 0;

  if (rank == 0) {
    read_file(input, arr_input_stdin);
    total_input_num = arr_input_stdin->count;

    int64_t* arr_new_input_num =
        (int64_t*)malloc(total_input_num * sizeof(int64_t));

    for (int index = 0; index < total_input_num; index++) {
      arr_new_input_num[index] = arr_input_stdin->elements[index];
    }

    for (int i = 1; i < process_count; ++i) {
      if (MPI_Send(&total_input_num, 1, MPI_INT, i, 0, MPI_COMM_WORLD) ==
          MPI_SUCCESS) {
        if (MPI_Send(arr_new_input_num, total_input_num, MPI_LONG_LONG_INT, i,
                     0, MPI_COMM_WORLD) != MPI_SUCCESS) {
          fprintf(stderr, "MPI Error: Could not send MPI Values\n");
        }
      } else {
        fprintf(stderr, "MPI Error: Could not send MPI Value count\n");
      }
    }
    free(arr_new_input_num);
  } else {
    if (MPI_Recv(&total_input_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE) == MPI_SUCCESS) {
      int64_t* arr_new_input_num =
          (int64_t*)malloc(total_input_num * sizeof(int64_t));
      if (MPI_Recv(arr_new_input_num, total_input_num, MPI_LONG_LONG_INT, 0, 0,
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
        fprintf(stderr, "MPI Error: Could not recv MPI Values\n");
      }
      for (int index = 0; index < total_input_num; index++) {
        array_append(arr_input_stdin, arr_new_input_num[index]);
      }
      free(arr_new_input_num);
    } else {
      fprintf(stderr, "MPI Error: Could not recv MPI Value Count\n");
    }
  }

  int64_t largest_element = largest_element_arr(arr_input_stdin);

  array_numbers_t* arr_prime_num =
      (array_numbers_t*)calloc(1, sizeof(array_numbers_t));
  array_init(arr_prime_num);
  trial_division(arr_prime_num, largest_element);

  goldbach(arr_input_stdin, arr_prime_num);

  struct timespec finish_time;
  clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &finish_time);

  double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
                   (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
  printf("execution time: %.9lfs\n", elapsed);

  array_destroy(arr_prime_num);
  array_destroy(arr_input_stdin);
  free(arr_prime_num);
  free(arr_input_stdin);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
