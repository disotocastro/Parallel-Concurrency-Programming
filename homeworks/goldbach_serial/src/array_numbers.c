/**
 * Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>
 * 
 * Créditos: Versión modificada del código de Jeisson Hidalgo, extraído 
 * de los videos "Taller de C++ a C"
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "array_numbers.h"

int array_init(array_numbers_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void array_destroy(array_numbers_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

int array_append(array_numbers_t* array, int64_t element) {
  if (array->count == array->capacity) {
    if ( array_increase_capacity(array) != EXIT_SUCCESS ) {
      return EXIT_FAILURE;
    }
  }
  
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}

int array_increase_capacity(array_numbers_t* array) {
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  int64_t* new_elements = (int64_t*)
    realloc(array->elements, new_capacity * sizeof(int64_t));

  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;

  } else {
    return EXIT_FAILURE;
  }
}
