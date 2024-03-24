#include "hello_iw_shr.hpp"

using namespace std;
mutex print_mutex;

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


  // 8. Use std::istringstream en lugar de sscanf().

  if (argc == 2) {
    istringstream iss(argv[1]);
    if (iss >> thread_count) {
    } else {
      cerr << "Error: invalid thread count\n " << endl;
      return 11;
    }
  }

  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));


  /**
   * 4. 
   * 
   * Mida la duración de ejecución con funcionalidad estándar como 
   * std::chrono::high_resolution_clock::now() en lugar de POSIX (clock_gettime)
  */

  try {
    shared_data->thread_count = thread_count;
    const auto start = chrono::high_resolution_clock::now();
    error = create_threads(shared_data);
    const auto end = chrono::high_resolution_clock::now();
    const chrono::duration<double> diff = end - start;

    cout << "Execution time:" << diff.count() << "s\n";
    free(shared_data);
  }
  catch(const exception& e) {
    cerr << "Error: could not allocate shared data: " << e.what() << endl;
    throw;
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
  throw;
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
    throw;
  }

} 