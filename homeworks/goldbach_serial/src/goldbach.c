// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "goldbach.h"

const int64_t MAX_INT64 = INT64_MAX;


int trial_division(array_numbers_t* arr_prime_numbers,
  int64_t largest_element) {
    assert(largest_element);
    assert(arr_prime_numbers);
  return EXIT_SUCCESS;
}

// Versión modificada de:
// https://www.geeksforgeeks.org/program-to-find-largest-element-in-an-array/

int64_t largest_element_arr(array_numbers_t* arr_input_stdin) {
  int64_t current_max_number = 0;

  for (int64_t index = 0; index < (int)arr_input_stdin->count; index++) {
    // se utiliza el valor absoluto porque los números pueden ser introducidos
    // como un -, ej: -8 para mostrar las sumas
    int64_t current_number = llabs(arr_input_stdin->elements[index]);
    if (current_number > current_max_number && current_number <= MAX_INT64) {
      current_max_number = current_number;
    }
  }  
  return current_max_number;
}
