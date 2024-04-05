// Copyright 2024 Diego Soto <juan.sotocastro.@ucr.ac.cr> CC-BY 4.0

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


// thread_shared_data_t
typedef struct shared_data {
  uint64_t position;
  pthread_mutex_t can_access_position;
  uint64_t thread_count;
  uint64_t pinata_count; // Contador de maximo de golpes
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;  // rank
  shared_data_t* shared_data;
  bool winner; // para saber quien rompio la pinata
  uint64_t thread_hit_counter; // Contador individual de cada hilo
  uint64_t pinata_count_priv; // Contador de maximo de golpes
} private_data_t;


void* attack(void* data);
int create_threads(shared_data_t* shared_data, int64_t pinata_count);

// procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  // create thread_count as result of converting argv[1] to integer
  // thread_count := integer(argv[1])
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  uint64_t pinata_count = 0;

  if (argc == 3) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    } else {
      fprintf(stderr, "Error: invalid thread count\n");
      return 11;
    }

    if (sscanf(argv[2], "%" SCNu64, &pinata_count) == 1) {
    } else {
      fprintf(stderr, "Error: invalid thread count\n");
      return 11;
    }
    printf("Pinata hits: %ld\n", pinata_count);

  }

  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    shared_data->position = 0;
    error = pthread_mutex_init(&shared_data->can_access_position, /*attr*/NULL);
    if (error == EXIT_SUCCESS) {
      shared_data->thread_count = thread_count;
      // Se agrega contador de pinata al shared data
      shared_data->pinata_count = pinata_count;

      struct timespec start_time, finish_time;
      clock_gettime(CLOCK_MONOTONIC, &start_time);

      error = create_threads(shared_data, pinata_count);

      clock_gettime(CLOCK_MONOTONIC, &finish_time);
      double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
        (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;

      printf("Execution time: %.9lfs\n", elapsed_time);

      pthread_mutex_destroy(&shared_data->can_access_position);
      free(shared_data);
    } else {
      fprintf(stderr, "Error: could not init mutex\n");
      return 13;
    }
  } else {
    fprintf(stderr, "Error: could not allocate shared data\n");
    return 12;
  }
  return error;
}  // end procedure


int create_threads(shared_data_t* shared_data, int64_t pinata_count) {
  int error = EXIT_SUCCESS;
  // for thread_number := 0 to thread_count do
  pthread_t* threads = (pthread_t*)
    malloc(shared_data->thread_count * sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(shared_data->thread_count, sizeof(private_data_t));
  if (threads && private_data) {
    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count
        ; ++thread_number) {
      private_data[thread_number].thread_number = thread_number;
      private_data[thread_number].shared_data = shared_data;
      private_data[thread_number].thread_hit_counter = 0;
      private_data[thread_number].winner = false; 
      private_data[thread_number].pinata_count_priv = pinata_count;

    
      // create_thread(greet, thread_number)
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, attack
        , /*arg*/ &private_data[thread_number]);
      if (error == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "Error: could not create secondary thread\n");
        error = 21;
        break;
      }
    }

    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count
        ; ++thread_number) {
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }

    free(private_data);
    free(threads);
  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64 " threads\n"
      , shared_data->thread_count);
    error = 22;
  }

  return error;
}

void* attack(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;

  while (true) {
    pthread_mutex_lock(&shared_data->can_access_position);
    if ( shared_data->pinata_count > 0 ) {
        // Si es el turno de este hilo para golpear la piñata
        shared_data->pinata_count--;
        // printf("%ld \n", shared_data->pinata_count);
        private_data->thread_hit_counter++;

        // Verificar si este hilo ha roto la piñata
        if ( shared_data->pinata_count == 0 ) {
          private_data->winner = true;
        }
    pthread_mutex_unlock(&shared_data->can_access_position);
    } else {
      // Si la piñata ya no puede recibir más golpes
      pthread_mutex_unlock(&shared_data->can_access_position);
        if (private_data->winner) {
          printf("Thread %ld / %ld: My hit num: %ld, I broke the pinata !! \n",
          private_data->thread_number, 
          private_data[0].pinata_count_priv,
          private_data->thread_hit_counter);
        } else {
          printf("Thread %ld / %ld: My hit num: %ld \n", 
          private_data->thread_number, 
          private_data[0].pinata_count_priv,
          private_data->thread_hit_counter);
        }
      break;
    }
  }

  return NULL;
}
