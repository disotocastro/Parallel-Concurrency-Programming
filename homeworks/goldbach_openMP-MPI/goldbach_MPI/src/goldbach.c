// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include "goldbach.h"

#include <math.h> /* Makefile LIBS= -lm */
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int64_t MAX_INT64 = INT64_MAX;

// Versión modificada de:
// https://www.geeksforgeeks.org/program-to-find-largest-element-in-an-array/

int64_t largest_element_arr(array_numbers_t* arr_input_stdin) {
  if (arr_input_stdin) {
  } else {
    fprintf(stderr, "Error: Could not read input numbers");
    return EXIT_FAILURE;
  }
  int64_t current_max_number = 0;
  int64_t current_number = 0;
  for (int64_t index = 0; index < (int)arr_input_stdin->count; index++) {
    // se utiliza el valor absoluto porque los números pueden ser introducidos
    // como un -, ej: -8 para mostrar las sumas
    current_number = llabs(arr_input_stdin->elements[index]);
    // if (numero_actual > numero_mas_grande y numero_actual <= MAXINT64)
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
  for (int64_t index = 2; index <= sqrt(num); index++) {
    if (num % index == 0) {
      return false;
    }
  }
  return true;
}

int64_t trial_division(array_numbers_t* arr_prime_numbers,
                       int64_t largest_element) {
  // arr_prime_numbers->count = 0;

  for (int64_t num = 2; num <= largest_element; num++) {
    if (is_prime(num)) {
      array_append(arr_prime_numbers, num);
    }
  }
  return EXIT_SUCCESS;
}

int64_t goldbach(array_numbers_t* arr_input_stdin,
                 array_numbers_t* arr_prime_numbers) {
  if (arr_input_stdin && arr_prime_numbers) {
    int64_t counter = (int64_t)arr_input_stdin->count;
    int64_t sums_counter = 0;
    int64_t goldbach_index = 0;

    for (int64_t main_index = 0; main_index < counter; main_index++) {
      array_numbers_t arr_goldbach;
      array_init(&arr_goldbach);
      int64_t current_num = arr_input_stdin->elements[main_index];
      printf("%ld:", current_num);

      // 5 < current_num < MAX_INT64
      if (5 < llabs(current_num) && llabs(current_num) < MAX_INT64) {
        // Si el número es par, conjetura fuerte:
        if (llabs(current_num) % 2 == 0) {
          if (goldbach_even(arr_input_stdin, arr_prime_numbers, &arr_goldbach,
                            main_index, goldbach_index,
                            sums_counter) != EXIT_SUCCESS) {
            fprintf(stderr, "Error: Could calculate even goldbach sums\n");
            return EXIT_FAILURE;
          }
        } else {
          // Como no es par, conjetura débil:
          if (goldbach_odd(arr_input_stdin, arr_prime_numbers, &arr_goldbach,
                           main_index, goldbach_index,
                           sums_counter) != EXIT_SUCCESS) {
            fprintf(stderr, "Error: Could calculate odd goldbach sums\n");
            return EXIT_FAILURE;
          }
        }
      } else {
        // Par casos como <= 5
        printf(" NA\n");
      }
      array_destroy(&arr_goldbach);
    }
  }
  return EXIT_SUCCESS;
}

int64_t goldbach_even(array_numbers_t* arr_input_stdin,
                      array_numbers_t* arr_prime_numbers,
                      array_numbers_t* arr_goldbach, int64_t main_index,
                      int64_t goldbach_index, int64_t sums_counter) {
  int64_t count = arr_prime_numbers->count;
  int64_t current_num = llabs(arr_input_stdin->elements[main_index]);
  int error = 0;

#pragma omp parallel for default(none)                                   \
    shared(arr_input_stdin, arr_prime_numbers, arr_goldbach, main_index, \
               goldbach_index, sums_counter, count, stderr, current_num, \
               error) schedule(dynamic) ordered
  for (int64_t i = 0; i < count; i++) {
    int64_t prime1 = arr_prime_numbers->elements[i];
    for (int64_t j = i; j < count; j++) {
      int64_t prime2 = arr_prime_numbers->elements[j];
      int64_t sum = prime1 + prime2;
      if (sum > current_num) break;

      if (sum == current_num) {
        if (arr_input_stdin->elements[main_index] < 0) {
#pragma omp ordered
          {
            if (array_append(arr_goldbach, prime1) != EXIT_SUCCESS ||
                array_append(arr_goldbach, prime2) != EXIT_SUCCESS) {
              fprintf(stderr, "Error: Could not add Goldbach sums\n");
              error = 1;
            }
          }
#pragma omp critical
          goldbach_index += 2;
        }
#pragma omp critical
        sums_counter++;
      }
    }
  }

  print_even(arr_input_stdin, arr_goldbach, main_index, goldbach_index,
             sums_counter);
  return error;
}

int64_t goldbach_odd(array_numbers_t* arr_input_stdin,
                     array_numbers_t* arr_prime_numbers,
                     array_numbers_t* arr_goldbach, int64_t main_index,
                     int64_t goldbach_index, int64_t sums_counter) {
  int64_t count = arr_prime_numbers->count;
  int64_t current_num = llabs(arr_input_stdin->elements[main_index]);
  int error = 0;

#pragma omp parallel for default(none) shared(                               \
        arr_input_stdin, arr_prime_numbers, arr_goldbach, main_index,        \
            goldbach_index, sums_counter, count, stderr, current_num, error) \
    schedule(dynamic) ordered  // 'ordered' para control de orden
  for (int64_t i = 0; i < count; i++) {
    int64_t prime1 = arr_prime_numbers->elements[i];
    for (int64_t j = i; j < count; j++) {
      int64_t prime2 = arr_prime_numbers->elements[j];
      for (int64_t k = j; k < count; k++) {
        int64_t prime3 = arr_prime_numbers->elements[k];
        int64_t sum = prime1 + prime2 + prime3;

        if (sum > current_num) break;

        if (sum == current_num) {
          if (arr_input_stdin->elements[main_index] < 0) {
#pragma omp ordered
            {
              if (array_append(arr_goldbach, prime1) != EXIT_SUCCESS ||
                  array_append(arr_goldbach, prime2) != EXIT_SUCCESS ||
                  array_append(arr_goldbach, prime3) != EXIT_SUCCESS) {
                fprintf(stderr, "Error: Could not add Goldbach sums\n");
                error = 1;
              }
            }
#pragma omp critical
            goldbach_index += 3;
          }
#pragma omp critical
          sums_counter++;
        }
      }
    }
  }
  print_odd(arr_input_stdin, arr_goldbach, main_index, goldbach_index,
            sums_counter);
  return error;
}
