/**
 * Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>
 * 
 * Créditos: Versión modificada del código de Jeisson Hidalgo, extraído 
 * de los videos "Hello_Order_Semaphor.c"
*/

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
#include "goldbach.h"

int create_threads(shared_data_t* shared_data) {
    sem_init(&shared_data->sem, 0, 1);
  // if (sem_init(&shared_data->sem, 0, 1)) {
    pthread_t* threads = (pthread_t*) calloc
                                 (shared_data->thread_count, sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*) calloc
                            (shared_data->thread_count, sizeof(private_data_t));

    if (threads && private_data) {
      // Crear semaforos
      for (uint64_t sem_index = 0; sem_index < shared_data->arr_input.count;
        sem_index++) {
        sem_init(&shared_data->can_print[sem_index], 0, !sem_index);
      }
      // Crear los hilos[i] y mem priv
      for (uint64_t i = 0; i < shared_data->thread_count; i++) {
        private_data[i].thread_number = i;
        private_data[i].shared_data = shared_data;
        if (pthread_create(&threads[i], NULL, run, &private_data[i]) == 0) {
        } else {
          fprintf(stderr, "Error: Could not create threads private memory\n");
          shared_data->thread_count = i;
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
    } else {
      fprintf(stderr, "Error: Could not create sems memory \n");
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

void* run(void* data) {
  size_t thread_index = 0;
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;

  pthread_mutex_lock(&shared_data->mutex);
  // sem_wait(&shared_data->sem);
  while (shared_data->this_thread_position < shared_data->arr_input.count) {
      thread_index = shared_data->this_thread_position;

      shared_data->this_thread_position++;
      pthread_mutex_unlock(&shared_data->mutex);
      // sem_post(&shared_data->sem);
      // Formula para calcular donde tiene que trabajar cada hilo
      // sem_t* next_thread = (&shared_data->can_print[thread_index + 1 %
      //   shared_data->arr_input.count]);

      goldbach(thread_index, &shared_data->arr_input,
               &shared_data->arr_prime_num,
               &shared_data->can_print[thread_index],
               (&shared_data->can_print[thread_index + 1 %
        shared_data->arr_input.count]));
    pthread_mutex_lock(&shared_data->mutex);
  }
  pthread_mutex_unlock(&shared_data->mutex);
  return NULL;
}
