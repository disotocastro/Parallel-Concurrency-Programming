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
  for (int64_t index = 2; index <= sqrt(num); index++) {
    if (num % index == 0) {
      return false;
    }
  }
  return true;
}

int64_t trial_division(array_numbers_t* arr_prime_numbers,
  int64_t largest_element) {
  //arr_prime_numbers->count = 0;

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
    int64_t counter = (int64_t) arr_input_stdin->count; // int64_t? cast
    int64_t sums_counter = 0;
    int64_t goldbach_index = 0;
    
    for (int64_t main_index = 0; main_index < counter; main_index++) {
      array_numbers_t arr_goldbach;
      array_init(&arr_goldbach);

      int64_t current_num = llabs(arr_input_stdin->elements[main_index]);
      printf("%ld:", current_num);

      // 5 < current_num < MAX_INT64
      if (5 < current_num && current_num < MAX_INT64) {
        if (current_num % 2 == 0) {
          goldbach_even(arr_input_stdin, arr_prime_numbers, &arr_goldbach, 
          main_index, goldbach_index, sums_counter);
        } else {
          goldbach_odd(arr_input_stdin, arr_prime_numbers, &arr_goldbach, 
          main_index, goldbach_index, sums_counter);
        }
      } else {
        printf(" NA\n");
      }
    }
  } 
  // else {
  //   fprintf(stderr, "Error: Could not find a correct input");
  //   return EXIT_FAILURE;
  // }
  
  return EXIT_SUCCESS;
}

int64_t goldbach_even(array_numbers_t* arr_input_stdin, 
  array_numbers_t* arr_prime_numbers, array_numbers_t* arr_goldbach,
  int64_t main_index, int64_t goldbach_index, int64_t sums_counter) {

  int64_t count = (int)arr_prime_numbers->count;  
  int64_t this_prime = 0;
  int64_t next_prime = 0;

  for (int64_t index_1 = 0; index_1 < count; index_1++) {
    for (int64_t index_2 = index_1; index_2 < count; index_2++) {
      this_prime =  arr_prime_numbers->elements[index_1]; 
      next_prime =  arr_prime_numbers->elements[index_2]; 

      if (this_prime != 0 && next_prime != 0) {
        if ((this_prime + next_prime) == llabs(arr_input_stdin->elements[main_index])) { 
          if (arr_input_stdin->elements[main_index] < 0) {
            array_append(arr_goldbach, this_prime);
            array_append(arr_goldbach, next_prime);
            goldbach_index += 2;
          }
          sums_counter++;
        }
      } 
      // else {
      //   fprintf(stderr, "Error: 0 is not a valid number. ");
      //   return EXIT_FAILURE;
      // }
    }
  }

  // Impresion
  printf(" %ld sums", sums_counter);
  if (arr_input_stdin->elements[main_index] < 0) {
    printf(": ");

    int64_t print_counter = goldbach_index;
    goldbach_index = 0;

    for (int i = 0; goldbach_index < print_counter; i++) {
      if (i > 0) {
          printf(", ");
      }
      printf("%ld + %ld", arr_goldbach->elements[goldbach_index], 
        arr_goldbach->elements[goldbach_index + 1]);
      goldbach_index += 2;
    }
  }
    printf("\n");
  return EXIT_SUCCESS;
}

int64_t goldbach_odd(array_numbers_t* arr_input_stdin, 
  array_numbers_t* arr_prime_numbers, array_numbers_t* arr_goldbach, 
  int64_t main_index, int64_t goldbach_index, int64_t sums_counter) {

  int64_t count = (int64_t) arr_prime_numbers->count;
  int64_t prime_1 =0;
  int64_t prime_2 =0;
  int64_t prime_3 =0;

  for (int64_t index_1 = 0; index_1 < count; index_1++) {
    for (int64_t index_2 = index_1; index_2 < count; index_2++) {
      for (int64_t index_3 = index_2; index_3 < count; index_3++) {

        prime_1 = (arr_prime_numbers->elements[index_1]); 
        prime_2 = (arr_prime_numbers->elements[index_2]); 
        prime_3 = (arr_prime_numbers->elements[index_3]); 

        if (prime_1 != 0 && prime_2 != 0 && prime_3 != 0) {
          if (prime_1 + prime_2 + prime_3 == llabs(arr_input_stdin->elements[main_index])) {
            if (arr_input_stdin->elements[main_index] < 0) {
              array_append(arr_goldbach, arr_prime_numbers->elements[index_1]);
              array_append(arr_goldbach, arr_prime_numbers->elements[index_2]);
              array_append(arr_goldbach, arr_prime_numbers->elements[index_3]);
              goldbach_index += 3;
            }
            sums_counter++;
          }
        } else {
          // error
        }
      }
    }
  }

  printf(" %ld sums", sums_counter);
  if (arr_input_stdin->elements[main_index] < 0) {
    printf(": ");
    int64_t print_counter = goldbach_index;
    goldbach_index = 0;
    for (int i = 0; goldbach_index < print_counter; i++) {
    if (i > 0) {
        printf(", ");
    }
      printf("%ld + %ld + %ld", arr_goldbach->elements[goldbach_index], 
        arr_goldbach->elements[goldbach_index+1], 
        arr_goldbach->elements[goldbach_index+2]);
      goldbach_index += 3;
    }
  }
  printf("\n");
  return EXIT_SUCCESS;
}
