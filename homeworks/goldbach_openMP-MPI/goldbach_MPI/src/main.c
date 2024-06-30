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
  analyze_arguments(argc, argv);
  MPI_Init(&argc, &argv);

  struct timespec start_time;
  clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &start_time);

  int rank = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtiene el rango del proceso actual

  int process_count = -1;
  // Obtiene el número total de procesos
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);

  FILE* input = stdin;  // Archivo de entrada desde la entrada estándar
  array_numbers_t* arr_input_stdin = (array_numbers_t*)calloc(
      1, sizeof(array_numbers_t));  // Inicializa un arreglo de números
  array_init(arr_input_stdin);      // Inicializa el arreglo

  // Lee el archivo si el proceso es el principal
  if (rank == 0) {
    read_file(input, arr_input_stdin);
  }

  int total_input_num = arr_input_stdin->count;

  // Broadcast del número total de números de entrada a todos los procesos
  MPI_Bcast(&total_input_num, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank != 0) {
    // Asigna memoria para los elementos de entrada si no es el proceso
    // principal
    arr_input_stdin->elements =
        (int64_t*)malloc(total_input_num * sizeof(int64_t));
    arr_input_stdin->count = total_input_num;
  }

  // Broadcast de los números de entrada a todos los procesos
  MPI_Bcast(arr_input_stdin->elements, total_input_num, MPI_LONG_LONG_INT, 0,
            MPI_COMM_WORLD);

  // Encuentra el mayor elemento
  int64_t largest_element = largest_element_arr(arr_input_stdin);

  // Inicializa un arreglo para números primos y los calcula mediante trial
  // division
  array_numbers_t* arr_prime_num =
      (array_numbers_t*)calloc(1, sizeof(array_numbers_t));
  array_init(arr_prime_num);
  trial_division(arr_prime_num, largest_element);

  // Determina la porción de la entrada que manejará cada proceso
  int64_t local_start = rank * total_input_num / process_count;
  int64_t local_end = (rank + 1) * total_input_num / process_count;

  // Inicializa un arreglo local para los números de entrada de cada proceso
  array_numbers_t* local_input =
      (array_numbers_t*)calloc(1, sizeof(array_numbers_t));
  array_init(local_input);
  for (int64_t i = local_start; i < local_end; ++i) {
    array_append(local_input, arr_input_stdin->elements[i]);
  }

  // Inicializa un arreglo local para los resultados de Goldbach de cada proceso
  array_numbers_t* local_goldbach_results =
      (array_numbers_t*)calloc(1, sizeof(array_numbers_t));
  array_init(local_goldbach_results);

  // Calcula las sumas de Goldbach para la porción local de números de entrada
  goldbach(local_input, arr_prime_num);

  // Recoge los resultados de vuelta al proceso raíz (rank 0)
  if (rank == 0) {
    // Inicializa un arreglo para los resultados globales de Goldbach
    array_numbers_t* global_goldbach_results =
        (array_numbers_t*)calloc(1, sizeof(array_numbers_t));
    array_init(global_goldbach_results);

    // Agrega los resultados locales al resultado global
    for (size_t i = 0; i < local_goldbach_results->count; ++i) {
      array_append(global_goldbach_results,
                   local_goldbach_results->elements[i]);
    }

    // Recoge los resultados de los otros procesos y los agrega al resultado
    // global
    for (int i = 1; i < process_count; ++i) {
      int64_t recv_count;
      MPI_Recv(&recv_count, 1, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      int64_t* recv_elements = (int64_t*)malloc(recv_count * sizeof(int64_t));
      MPI_Recv(recv_elements, recv_count, MPI_LONG_LONG_INT, i, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      for (int64_t j = 0; j < recv_count; ++j) {
        array_append(global_goldbach_results, recv_elements[j]);
      }
      free(recv_elements);
    }

    // Imprime los resultados globales
    for (size_t i = 0; i < global_goldbach_results->count; ++i) {
      printf("%ld\n", global_goldbach_results->elements[i]);
    }

    array_destroy(global_goldbach_results);
    free(global_goldbach_results);

  } else {
    // Envía los resultados locales al proceso raíz
    MPI_Send(&local_goldbach_results->count, 1, MPI_LONG_LONG_INT, 0, 0,
             MPI_COMM_WORLD);
    MPI_Send(local_goldbach_results->elements, local_goldbach_results->count,
             MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
  }

  struct timespec finish_time;
  clock_gettime(/*clk_id*/ CLOCK_MONOTONIC,
                &finish_time);  // Obtiene el tiempo de finalización

  double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
                   (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
  if (rank == 0) {
    printf("execution time: %.9lfs\n", elapsed);
  }

  // Libera la memoria y finaliza MPI
  array_destroy(arr_prime_num);
  array_destroy(arr_input_stdin);
  array_destroy(local_input);
  array_destroy(local_goldbach_results);
  free(arr_prime_num);
  free(arr_input_stdin);
  free(local_input);
  free(local_goldbach_results);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
