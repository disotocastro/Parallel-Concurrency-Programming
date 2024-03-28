/**
 * Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>
 * 
 * Créditos: Versión modificada del código de Jeisson Hidalgo, extraído 
 * de los videos "Taller de C++ a C"
*/

#ifndef ARRAY_NUMBERS_H
#define ARRAY_NUMBERS_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  size_t capacity;
  size_t count;
  int64_t* elements;
} array_numbers_t;

/**
 * @brief Se encarga de incializar el array de números enteros (int64)
 * 
 * @param array: Array de números enteros (int64)
*/
int array_init(array_numbers_t* array);

/**
 * @brief Se encarga de destruir la memoría utilizada por el array
 * 
 * @param array: Array de números enteros (int64)
*/
void array_destroy(array_numbers_t* array);

/**
 * @brief Se encarga de introducir un nuevo elemento en el array
 * 
 * @param array: Array de números enteros (int64)
 * @param element: Número entero (int64)
*/
int array_append(array_numbers_t* array, int64_t element);

#endif  // ARRAY_NUMBERS_H