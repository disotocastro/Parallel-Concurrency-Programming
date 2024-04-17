// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#include <stdbool.h>
#include <stdio.h>

#include "common.h"
#include "consumer.h"

void* consume(void* data) {
  // Se inicia una simulacion desde la memoria privada del hilo
  private_memory_t* thread_memory = (private_memory_t*)data;
  simulation_t* simulation = thread_memory->simulation;
  thread_memory->thread = pthread_self();

  while (true) {
    // Solo se puede consumir un paquete a la vez
    pthread_mutex_lock(&simulation->mutex_next_unit);
      if (simulation->consumed_count < simulation->unit_count) {
      ++simulation->consumed_count;
    } else {
      // Consumo terminado...
      pthread_mutex_unlock(&simulation->mutex_next_unit);
      break; 
    }
    pthread_mutex_unlock(&simulation->mutex_next_unit);

    sem_wait(&simulation->can_consume);
    size_t value = 0;
    queue_dequeue(&simulation->queue, &value);
    printf("\tConsuming %zu\n", value);
    usleep(1000 * random_between(simulation->consumer_min_delay
    , simulation->consumer_max_delay));
  }
  return NULL;
}
