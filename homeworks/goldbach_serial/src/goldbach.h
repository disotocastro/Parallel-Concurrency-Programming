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

int trial_division(array_numbers_t* arr_prime_numbers, int64_t largest_element);
int64_t largest_element_arr();


#endif // GOLDBACH_H