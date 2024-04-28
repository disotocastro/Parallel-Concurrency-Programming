// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

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
  if (!arr_input_stdin || arr_input_stdin->count == 0) {
    fprintf(stderr, "Error: Could not read input numbers");
    return EXIT_FAILURE;
  }

  int64_t current_max_number = 0;
  const size_t count = arr_input_stdin->count;

  for (size_t index = 0; index < count; index++) {
    // se utiliza el valor absoluto porque los números pueden ser introducidos
    // como un -, ej: -8 para mostrar las sumas
    int64_t current_number = llabs(arr_input_stdin->elements[index]);
    // if (numero_actual > numero_mas_grande y numero_actual <= MAXINT64)
    if (current_number > current_max_number) {
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

int64_t goldbach(size_t index, array_numbers_t* arr_input_stdin,
  array_numbers_t* arr_prime_numbers, sem_t* can_print, sem_t* next_thread) {
  if (arr_input_stdin && arr_prime_numbers) {
    int64_t sums_counter = 0;
    int64_t goldbach_index = 0;
    array_numbers_t arr_goldbach;
    array_init(&arr_goldbach);
    int64_t current_num = arr_input_stdin->elements[index];

    // 5 < current_num < MAX_INT64
    if (5 < llabs(current_num) && llabs(current_num) < MAX_INT64) {
      // Si el número es par, conjetura fuerte:
      if (llabs(current_num) % 2 == 0) {
        if (goldbach_even(arr_input_stdin, arr_prime_numbers, &arr_goldbach,
            index, goldbach_index, sums_counter, can_print, next_thread)
            != EXIT_SUCCESS) {
          fprintf(stderr, "Error: Could calculate even goldbach sums\n");
          return EXIT_FAILURE;
        }
      } else {
        // Como no es par, conjetura débil:
        if (goldbach_odd(arr_input_stdin, arr_prime_numbers, &arr_goldbach,
          index, goldbach_index, sums_counter, can_print, next_thread)
            != EXIT_SUCCESS) {
          fprintf(stderr, "Error: Could calculate odd goldbach sums\n");
          return EXIT_FAILURE;
        }
        }
    } else {
      // Para casos como <= 5
      sem_wait(can_print);
      printf("%ld:", current_num);
      printf(" NA\n");
      sem_post(next_thread);
    }
    array_destroy(&arr_goldbach);
  }
  return EXIT_SUCCESS;
}

int64_t goldbach_even(array_numbers_t* arr_input_stdin,
  array_numbers_t* arr_prime_numbers, array_numbers_t* arr_goldbach,
  int64_t main_index, int64_t goldbach_index, int64_t sums_counter,
  sem_t* can_print, sem_t* next_thread) {
    for (size_t index_1 = 0; index_1 < arr_prime_numbers->count; index_1++) {
      for (size_t index_2 = index_1; index_2 < arr_prime_numbers->count;
        index_2++) {
        if (arr_prime_numbers->elements[index_1] &&
            arr_prime_numbers->elements[index_2] &&
            (arr_prime_numbers->elements[index_1] +
             arr_prime_numbers->elements[index_2]) ==
          llabs(arr_input_stdin->elements[main_index])) {
          if (arr_input_stdin->elements[main_index] < 0) {
            if (array_append(arr_goldbach,
                arr_prime_numbers->elements[index_1]) != EXIT_SUCCESS) {
                fprintf(stderr, "Error: Could not add goldbach sums\n");
                return EXIT_FAILURE;
            }
            if (array_append(arr_goldbach,
                arr_prime_numbers->elements[index_2]) != EXIT_SUCCESS) {
                fprintf(stderr, "Error: Could not add goldbach sums\n");
                return EXIT_FAILURE;
            }
            goldbach_index += 2;
          }
          sums_counter++;
        }
      }
    }

    sem_wait(can_print);
    print_even(arr_input_stdin, arr_goldbach,
               main_index, goldbach_index, sums_counter);
    sem_post(next_thread);
    return EXIT_SUCCESS;
}

int64_t goldbach_odd(array_numbers_t* arr_input_stdin,
  array_numbers_t* arr_prime_numbers, array_numbers_t* arr_goldbach,
  int64_t main_index, int64_t goldbach_index, int64_t sums_counter,
  sem_t* can_print, sem_t* next_thread) {
  int64_t count = (int64_t) arr_prime_numbers->count;
  for (int64_t index_1 = 0; index_1 < count; index_1++) {
    for (int64_t index_2 = index_1; index_2 < count; index_2++) {
      for (int64_t index_3 = index_2; index_3 < count; index_3++) {
        if (arr_prime_numbers->elements[index_1] != 0 &&
            arr_prime_numbers->elements[index_2] != 0 &&
            arr_prime_numbers->elements[index_3] != 0) {
          if (arr_prime_numbers->elements[index_1] +
              arr_prime_numbers->elements[index_2] +
              arr_prime_numbers->elements[index_3] ==
              llabs(arr_input_stdin->elements[main_index])) {
            if (arr_input_stdin->elements[main_index] < 0) {
              if (array_append(arr_goldbach,
                arr_prime_numbers->elements[index_1]) != EXIT_SUCCESS) {
                fprintf(stderr, "Error: Could not add goldbach sums\n");
                return EXIT_FAILURE;
              }
              if (array_append(arr_goldbach,
                arr_prime_numbers->elements[index_2]) != EXIT_SUCCESS) {
                fprintf(stderr, "Error: Could not add goldbach sums\n");
                return EXIT_FAILURE;
              }
              if (array_append(arr_goldbach,
                arr_prime_numbers->elements[index_3]) != EXIT_SUCCESS) {
                fprintf(stderr, "Error: Could not add goldbach sums\n");
                return EXIT_FAILURE;
              }
              goldbach_index += 3;
            }
            sums_counter++;
          }
        }
      }
    }
  }
  sem_wait(can_print);
  print_odd(arr_input_stdin, arr_goldbach, main_index,
            goldbach_index, sums_counter);
  sem_post(next_thread);
  return EXIT_SUCCESS;
}
