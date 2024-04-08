#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// thread_shared_data_t
typedef struct shared_data {
  uint64_t next_thread;
  uint64_t thread_count;
  double delay;  // delay microseconds
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;  // rank
  shared_data_t* shared_data;
} private_data_t;

/**
 * @brief ...
 */
void* greet(void* data);
int create_threads(shared_data_t* shared_data);

// procedure main(argc, argv[])
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  // create thread_count as result of converting argv[1] to integer
  // thread_count := integer(argv[1])
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  double seconds, microseconds = 0.0;

    if (argc == 3) {
      if (sscanf(argv[1], "%" SCNu64, &thread_count) != 1) {
        fprintf(stderr, "Error: invalid thread count\n");
        return 10;
      }

      if (sscanf(argv[2], "%lf", &seconds) != 1 || seconds <= 0) {
        fprintf(stderr, "Error: invalid seconds\n");
        return 3;
      }
      // Conversion a nanosegundos
      microseconds = seconds * 1e-6;
      printf("Busy-wait Time: %.6lfµs\n", microseconds);
    }

  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    shared_data->next_thread = 0;
    shared_data->thread_count = thread_count;
    shared_data->delay = microseconds;

    struct timespec start_time, finish_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    error = create_threads(shared_data);

    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;

    printf("Random seed Execution time: %.9lfs\n", elapsed_time);

    free(shared_data);
  } else {
    fprintf(stderr, "Error: could not allocate shared data\n");
    return 12;
  }
  return error;
}  // end procedure


int create_threads(shared_data_t* shared_data) {
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
      // create_thread(greet, thread_number)
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, greet
        , /*arg*/ &private_data[thread_number]);
      if (error == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "Error: could not create secondary thread\n");
        error = 21;
        break;
      }
    }

    // print "Hello from main thread"
    printf("Hello from main thread\n");

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

// procedure greet:
void* greet(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;
  // Cantidad maxima de hilos: 32751.
  // Version con tiempo de espera constante
  #if 0
    while (shared_data->next_thread < private_data->thread_number) {
      usleep(shared_data->delay);
    }
  #endif

  #if 1
    while (shared_data->next_thread < private_data->thread_number) {
      unsigned int seed = clock();
      const double scale = shared_data->delay / (double)RAND_MAX;
      float my_delay = (float)rand_r(&seed) * scale;

      usleep(my_delay);
    }
  #endif

  // print "Hello from secondary thread"
  // printf("Hello from secondary thread %" PRIu64 " of %" PRIu64 "\n"
  //   , private_data->thread_number, shared_data->thread_count);

  // Allow subsequent thread to do the task
  ++shared_data->next_thread;

  return NULL;
}  // end procedure
