/**
 * Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>
 * 
 * Créditos: Versión modificada del código de Jeisson Hidalgo, extraído 
 * de los videos "Hello_Order_Semaphor.c"
*/

#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// thread_shared_data_t
typedef struct shared_data {
  sem_t* can_print;
  uint64_t thread_count;
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;  // rank
  shared_data_t* shared_data;
} private_data_t;

/**
 * @brief ...
 * 
 * @param argc, argv: Argumentos dados por el usuario
 * @param argv[2]: Numero de hilos de la computadora
*/
int golbach_concurrency(int argc, char* argv[]);

/**
 * @brief  ...
 * 
 * @param shared_data:
*/
int create_threads(shared_data_t* shared_data);

/**
 * @brief 
 * 
 * @param data:
*/
void* run(void* data);

#endif  // CONCURRENCY_H
