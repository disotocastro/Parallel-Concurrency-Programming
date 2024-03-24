#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Cambios en las bibliotecas
#include <thread>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include<exception>
#include <cstdint>
#include <mutex> 



using namespace std;
mutex print_mutex;

typedef struct shared_data {
  uint64_t thread_count;
} shared_data_t;


typedef struct private_data {
  uint64_t thread_number;  // rank
  shared_data_t* shared_data;
} private_data_t;

void* greet(void* data);
int create_threads(shared_data_t* shared_data);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;

  uint64_t thread_count = thread::hardware_concurrency();

  /**
   * 2. 
   * 
   * Obtenga la cantidad de CPUs disponibles en el sistema usando funcionalidad 
   * de la clase std::thread en lugar de POSIX.
   * 
   * LISTO.
  */

  if (argc == 2) {
    istringstream iss(argv[1]);
    if (iss >> thread_count) {
    } else {
      cerr << "Error: invalid thread count\n " << endl;
      return 11;
    }
  }

  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  
  try {
    shared_data->thread_count = thread_count;
    struct timespec start_time, finish_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    error = create_threads(shared_data);
    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
    // printf("Execution time: %.9lfs\n", elapsed_time);
    std::cout << "Execution time:" << elapsed_time<<std::endl;
    free(shared_data);
  }
  catch(const std::exception& e) {
    std::cerr << " Error: could not allocate shared data\n " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  
  return error;
}  

int create_threads(shared_data_t* shared_data) {

  try {
    int error = EXIT_SUCCESS;

    /**
     * 3.
     *  
     * Use un arreglo dinámico para almacenar los objetos que controlan los hilos
     * de ejecución. Dado que estos objetos deben recibir en su constructor la 
     * rutina que se va a ejecutar en un hilo aparte, agréguelos al vector con el 
     * método emplace_back()
     * 
     * LISTO.
    */
    vector<thread> threads;
    vector<private_data_t> private_data;

    /**
     * 4. 
     * 
     * Use un arreglo dinámico para alojar los datos privados de los hilos de  
     * ejecución. Aproveche que conoce el tamaño del arreglo de antemano para  
     * crearlo de la capacidad justa. 
     * 
     * LISTO
    */


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
    }
    cout << "Hello from main thread\n" << endl;

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
 catch(const std::exception& e) {
  std::cerr << e.what() << '\n';
  return EXIT_FAILURE;
 }
 
}

void* greet(void* data) {
  try { 
    private_data_t* private_data = (private_data_t*) data;
    shared_data_t* shared_data = private_data->shared_data;

    // El mutex evita que el print de desordene, ya que sin esto los prints
    // se podian desincronizar
    print_mutex.lock();
    cout << "Hello from secondary thread " << private_data->thread_number 
      << " of " << shared_data->thread_count << endl;
    print_mutex.unlock();

    return NULL;
  }
  catch(const std::exception& e) {
    std::cerr << "Error: Could not create threads "<< e.what() << '\n';
    return;
  }

} 


/***
 * 1. Listo
 * 2 Listo
 * 3 Listo
 * 4 ..
 * 5 ..
 * 6. LISTO
 * 7. LISTO
 * 8. LISTO
 * 
 * 10. LISTO
 * 
 * 
*/