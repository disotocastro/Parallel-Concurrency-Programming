#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#include "array_numbers.h"
#include "file_read_out.h"
#include "concurrency.h"


// Este codigo funciona de manera muy similar al antiguo main
int golbach_concurrency(int argc, char* argv[]) {
  FILE* input = stdin;
  int error = EXIT_SUCCESS;
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));

  if (shared_data) {
    shared_data->thread_count = get_thread_count(argc, argv);
    fprintf("Num of threds%ld", shared_data->thread_count);
    shared_data->this_thread_position = 0;
    // analizar_argumentos(argc, argv);
    // array_usuario = leer_input_usuario(input_usuario);
    analyze_arguments(argc, argv);
    array_init(&shared_data->arr_input);
    read_file(input, &shared_data->arr_input);    

    int64_t largest_element = largest_element_arr(&shared_data->arr_input);
    array_init(&shared_data->arr_prime_num);
    trial_division(&shared_data->arr_prime_num, largest_element);
    shared_data->can_print = (sem_t*) calloc
                                (shared_data->arr_input.count, sizeof(sem_t));
    if (shared_data->can_print) {
      create_threads(shared_data);
      free(shared_data->can_print);
    } else {
      fprintf(stderr, "Error: Could not allocate semaphores\n");
      error = EXIT_FAILURE;
    }
    array_destroy(&shared_data->arr_prime_num);
    array_destroy(&shared_data->arr_input);
    free(shared_data);
  }
  else{
    fprintf(stderr, "Error: Could not create dynamic memory\n");
    error = EXIT_FAILURE;
  }
  return error;
}

int create_threads(shared_data_t* shared_data) {
  if (sem_init(&shared_data->sem,0, 1)) {
    // Camino feliz
    pthread_t* threads = (pthread_t*) calloc
                                 (shared_data->thread_count, sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*) calloc
                            (shared_data->thread_count, sizeof(private_data_t));

    if (threads && private_data) {
      // Crear semaforos
      for (uint64_t sem_index = 0; sem_index < shared_data->arr_input.count; 
        sem_index++) {
        
        if (sem_init(&shared_data->can_print[sem_index], 0, !sem_index)) {
          
        } else {
          return EXIT_FAILURE;
        }
      }
      // Crear los hilos[i] y mem priv
      for (uint64_t i = 0; i < shared_data->thread_count; i++) {
        private_data[i].thread_number = i;
        private_data[i].shared_data = shared_data;
        if (pthread_create(&threads[i], NULL, run, &private_data[i]) == 0) {
          
        } else {
          shared_data->thread_count = i;
          // implementar codigo de error
          return EXIT_FAILURE;
          break;
        }
      }
      // Limpiar mem
      for (uint64_t i = 0; i < shared_data->thread_count; ++i) {
        pthread_join(threads[i], NULL);
        sem_destroy(&shared_data->can_print[i]);
      }
      free(threads);
      free(private_data);
    } else{
      // Implementar error aqui
      return EXIT_FAILURE;
    }
  } else {
    fprintf(stderr, "Error: Could not create sems memory\n");
    return EXIT_FAILURE;
  }
}

void* run(void* data) {
  
}