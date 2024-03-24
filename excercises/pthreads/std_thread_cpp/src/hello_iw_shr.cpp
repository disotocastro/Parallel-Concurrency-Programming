#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Cambios en las bibliotecas
#include <thread>
#include <iostream>
#include <cstdlib>
#include <vector>




/**
 * 1. Cambiar nombre y extension: LISTO
 * 
 * 2. Obtenga la cantidad de CPUs disponibles en el sistema usando 
 * funcionalidad de la clase std::thread en lugar de POSIX. LISTO
 * 
 * 3. Vectores. LISTO
 * 
 * 4. Ultimo
 * 
 * 
 * 
 * 
*/

// thread_shared_data_t
typedef struct shared_data {
  uint64_t thread_count;
} shared_data_t;

// thread_private_data_t
typedef struct private_data {
  uint64_t thread_number;  // rank
  shared_data_t* shared_data;
} private_data_t;
using namespace std; 

void* greet(void* data);
int create_threads(shared_data_t* shared_data);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  
  /**
   * 2. 
   * 
   * Obtenga la cantidad de CPUs disponibles en el sistema usando funcionalidad 
   * de la clase std::thread en lugar de POSIX.
  */

  uint64_t thread_count = std::thread::hardware_concurrency();

  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    } else {
      fprintf(stderr, "Error: invalid thread count\n");
      return 11;
    }
  }

  /**
   * 5. 
   * 
   * Use manejo de memoria dinámica de C++ (new) para los datos compartidos 
   * de los hilos. Es recomendable usar un puntero inteligente 
   * (std::shared_ptr<>) para este fin.
  */

  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));


  if (shared_data) {
    shared_data->thread_count = thread_count;

    struct timespec start_time, finish_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    error = create_threads(shared_data);

    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;

    printf("Execution time: %.9lfs\n", elapsed_time);

    free(shared_data);
  } else {
    fprintf(stderr, "Error: could not allocate shared data\n");
    return 12;
  }
  return error;
}  // end procedure

int create_threads(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;
/**
   * 3.
   *  
   * Use un arreglo dinámico para almacenar los objetos que controlan los hilos
   * de ejecución. Dado que estos objetos deben recibir en su constructor la 
   * rutina que se va a ejecutar en un hilo aparte, agréguelos al vector con el 
   * método emplace_back()
   * 
  */

  // pthread_t* threads = (pthread_t*)
  //   malloc(shared_data->thread_count * sizeof(pthread_t));
  // private_data_t* private_data = (private_data_t*)
  //   calloc(shared_data->thread_count, sizeof(private_data_t));

  vector<thread> threads;
  vector<private_data_t> private_data;
  // Reservar el espacio para los vectores
  threads.reserve(shared_data->thread_count);
  private_data.reserve(shared_data->thread_count);

    for (uint64_t thread_number = 0; thread_number < shared_data->thread_count
        ; ++thread_number) {

      // private_data[thread_number].thread_number = thread_number;
      // private_data[thread_number].shared_data = shared_data;
      private_data.emplace_back();
      private_data.back().thread_number = thread_number;
      private_data.back().shared_data = shared_data;
      threads.emplace_back(greet, &private_data.back());

      // print "Hello from main thread"
      printf("Hello from main thread\n");

    }
    // for (int i = 0; i < threads.size(); ++i) {
    //   threads[i].join();
    // }

    for (thread& thread : threads) {
      thread.join();
    }

    threads.clear();
    private_data.clear();
  
  return error;
}

// procedure greet:
void* greet(void* data) {
  // assert(data);
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;

  // print "Hello from secondary thread"
  printf("Hello from secondary thread %" PRIu64 " of %" PRIu64 "\n"
    , private_data->thread_number, shared_data->thread_count);
  return NULL;
}  // end procedure
