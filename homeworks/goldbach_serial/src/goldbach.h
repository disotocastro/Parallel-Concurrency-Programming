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

/**
 * @brief Realiza la "trial division" metodo para encontrar todos los números 
 * primos hasta el número más grande dado y los almacena en un arreglo dinámico.
 * 
 * @param arr_prime_numbers Un puntero al arreglo dinámico donde 
 * se almacenarán los números primos encontrados.
 * @param largest_element Número más grande dado por usuario, hasta este número
 * se va a realizar los cálculos de los números primos.
 * @return EXIT_SUCCESS si la función se ejecuta correctamente.
 */
 int64_t trial_division(array_numbers_t* arr_prime_numbers,
  int64_t largest_element);

/**
 * @brief Determina si un número entero es primo.
  
 * @param num El número entero que se va a verificar.
 * @return true si el número es primo, false si no lo es.
 */
 bool is_prime(int64_t num);


/**
 * @brief Se encarga de dividir el trabajo en 2, uno para la conjetura fuerte
 * y otro para la conjetura débil, dependiendo de que número sea, se llamará
 * a al conjetura que corresponda.
 * 
 * @param arr_input_stdin array de datos ingresado por el usuario
 * @param arr_prime_numbers array de numeros primos, de los numeros ingresados
 * por el usuario
 * @return EXIT_SUCCESS si la función se ejecuta correctamente.

 */
int64_t goldbach(array_numbers_t* arr_input_stdin,
  array_numbers_t* arr_prime_numbers);


int64_t goldbach_even(array_numbers_t* arr_input_stdin, 
  array_numbers_t* arr_prime_numbers, array_numbers_t* arr_goldbach, 
  int64_t main_index, int64_t goldbach_index, int64_t sums_counter);

#endif  // GOLDBACH_H
