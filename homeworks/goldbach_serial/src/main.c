// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_read_out.h"
#include "array_numbers.h"
#include "goldbach.h"

int main(int argc, char* argv[]) {
  // analizar_argumentos(argc, argv);
  analyze_arguments(argc, argv);

  // array_usuario = leer_input_usuario(input_usuario);
  FILE* input = stdin;
  array_numbers_t* arr_input_stdin = (array_numbers_t*)
    calloc(1, sizeof(array_numbers_t));
  array_init(arr_input_stdin);
  read_file(input, arr_input_stdin);

  // input_mas_grande = elemento_mas_grande_array(array_usuario)
  int64_t largest_element = largest_element_arr(arr_input_stdin);
  // array_numeros_primos = trial_division(array_usuario, input_mas_grande)
  array_numbers_t* arr_prime_num = (array_numbers_t*)
    calloc(1, sizeof(array_numbers_t));
  array_init(arr_prime_num);
  trial_division(arr_prime_num, largest_element);

  /**
   * En caso de que se quiera, para imprimir todos los numeros
   * primos encotrados:
   * 
   * for (size_t i = 0; i < arr_prime_num.count; i++) {
   *   printf("ALL PRIME NUMS %" PRId64 "\n", arr_prime_num.elements[i]);
   * }
   *
  */
  
  // goldbach(array_usuario, array_numeros_primos)
  goldbach(arr_input_stdin, arr_prime_num);
  array_destroy(arr_prime_num);
  array_destroy(arr_input_stdin);
  free(arr_prime_num);
  free(arr_input_stdin);
    
  return EXIT_SUCCESS;
}
