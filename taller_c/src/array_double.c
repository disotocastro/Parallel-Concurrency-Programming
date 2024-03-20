#include <array_double.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int array_double_increase_capacity(array_double_t* array);

// aqui se documenta el doxy
int array_double_init(array_double_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void array_double_destroy(array_double_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

int array_double_append(array_double_t* array, double element) {
  assert(array);
  // cuando no hay capacidad
  if (array->count == array->capacity){
    if (array_double_increase_capacity(array) != EXIT_SUCCESS ) {
      return EXIT_FAILURE;
    }
  }
  
  array->elements[array->count++] = element; 
  return EXIT_SUCCESS;
}

int array_double_increase_capacity(array_double_t* array){
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  double* new_elements = (double*) 
    realloc(array->elements, new_capacity * sizeof(double));

  if (new_elements) {
    array->capacity = new_capacity; 
    array->elements = new_elements;
    return EXIT_SUCCESS;

  } else{
    return EXIT_FAILURE;
  }
  

}


