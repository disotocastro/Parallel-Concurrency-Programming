// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#ifndef GOLDBACH_H
#define GOLDBACH_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_read_out.h"
#include "array_numbers.h"

/**
 * @brief Busca y retorna el número más grande del array
 * 
 * @param arr_input_stdin: Array de números enteros (int64)
*/
int64_t largest_element_arr(array_numbers_t* arr_input_stdin);

int trial_division(array_numbers_t* arr_prime_numbers, int64_t largest_element);


#endif  // GOLDBACH_H
