// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>  /* Makefile LIBS= -lm */

#include "goldbach.h"

const int64_t MAX_INT64 = INT64_MAX;

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


/**
 * Trial_Division y is_prime, es una versión adaptada del código de:
 * https://literateprograms.org/trial_division__c_.html
 * 
 * Aquí también se mencionan formas de optmización, como 
 * <<trial division with prime divisors only>>, que puede ser utilziada
 * más adelante para optimizar aún más la tarea
*/

bool is_prime(int64_t num) {
  if (num <= 1) return false;
  if (num <= 3) return true;

  // Comprobamos si el número es divisible por algún divisor hasta su sqrt(num)
  for (int64_t i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int64_t trial_division(array_numbers_t* arr_prime_numbers,
  int64_t largest_element) {
  arr_prime_numbers->count = 0;

  for (int64_t num = 2; num <= largest_element; num++) {
    if ((num)) {
      array_append(arr_prime_numbers, num);
    }
  }
  return EXIT_SUCCESS;
}
