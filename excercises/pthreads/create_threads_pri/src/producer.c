// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdio.h>

#include "common.h"
#include "producer.h"

void* produce(void* data) {
  // Se inicia una simulacion desde la memoria privada del hilo
  private_memory_t* thread_memory = (private_memory_t*)data;
  simulation_t* simulation = thread_memory->simulation;
  thread_memory->thread = pthread_self();

  while (true) {
    size_t my_unit = 0;
    // Mutex para que solo pueda trabajar un hilo
    pthread_mutex_lock(&simulation->mutex_next_unit);
    // Si hay trabajo pendiente...
      if (simulation->next_unit < simulation->unit_count) {
        my_unit = ++simulation->next_unit;
      } else {
        // Trabajo terminado...
        pthread_mutex_unlock(&simulation->mutex_next_unit);
        break; 
      }   
    pthread_mutex_unlock(&simulation->mutex_next_unit);

    usleep(1000 * random_between(simulation->producer_min_delay
      , simulation->producer_max_delay));
    queue_enqueue(&simulation->queue, my_unit);
    printf("Produced %zu\n", my_unit);

    // Señal de que ya se puede consumir
    sem_post(&simulation->can_consume);
  }

  return NULL;
}