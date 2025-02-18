// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4

#ifndef COMMON_H
#define COMMON_H

#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#include "queue.h"

enum {
  ERR_NOMEM_SHARED = EXIT_FAILURE + 1,
  ERR_NOMEM_BUFFER,
  ERR_NO_ARGS,
  ERR_UNIT_COUNT,
  ERR_PRODUCER_COUNT,
  ERR_CONSUMER_COUNT,
  ERR_MIN_PROD_DELAY,
  ERR_MAX_PROD_DELAY,
  ERR_MIN_CONS_DELAY,
  ERR_MAX_CONS_DELAY,
  ERR_CREATE_THREAD,
};

typedef struct simulation {
  size_t unit_count;
  size_t producer_count;
  size_t consumer_count;
  useconds_t producer_min_delay;
  useconds_t producer_max_delay;
  useconds_t consumer_min_delay;
  useconds_t consumer_max_delay;

  pthread_mutex_t mutex_next_unit; 
  pthread_mutex_t mutex_consumed_count;
  sem_t can_consume; 
  queue_t queue;
  size_t next_unit;
  size_t consumed_count;
} simulation_t;

typedef struct private_memory {
  size_t thread_id;
  size_t thread_count;
  pthread_t thread;
  simulation_t *simulation;
} private_memory_t;


useconds_t random_between(useconds_t min, useconds_t max);

#endif  // COMMON_H
