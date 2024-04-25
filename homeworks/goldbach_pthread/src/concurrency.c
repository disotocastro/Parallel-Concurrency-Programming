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


// Este codigo funciona de manera muy similar al antiguo main
int golbach_concurrency(int argc, char* argv[]) {
  FILE* input = stdin;
  int error = EXIT_SUCCESS;
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));

  if (shared_data) {
    shared_data->thread_count = get_thread_count(argc, argv);
    fprintf("Num of threds%ld", shared_data->thread_count);
    shared_data->this_thread_position = 0;

    // analizar_argumentos(argc, argv);
    // array_usuario = leer_input_usuario(input_usuario);
    analyze_arguments(argc, argv);
    array_init(&shared_data->arr_input);
    read_file(input, &shared_data->arr_input);    

    int64_t largest_element = largest_element_arr(&shared_data->arr_input);
    array_init(&shared_data->arr_prime_num);
    trial_division(&shared_data->arr_prime_num, largest_element);

    shared_data->can_print = (sem_t*) calloc(shared_data->arr_input.count, 
                                                                 sizeof(sem_t));
    if (shared_data->can_print) {
      create_threads(shared_data);
      free(shared_data->can_print);
    } else {
      fprintf(stderr, "Error: Could not allocate semaphores\n");
      error = EXIT_FAILURE;
    }
    array_destroy(&shared_data->arr_prime_num);
    array_destroy(&shared_data->arr_input);
    free(shared_data);                                                                
  }
  else{
    fprintf(stderr, "Error: Could not create dynamic memory\n");
    error = EXIT_FAILURE;    
  }
  return error;
}

int create_threads(shared_data_t* shared_data) {

}

void* run(void* data) {

}