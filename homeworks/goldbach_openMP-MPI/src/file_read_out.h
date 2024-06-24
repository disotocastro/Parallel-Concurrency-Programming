// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#ifndef FILE_READ_OUT_H
#define FILE_READ_OUT_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "array_numbers.h"

/**
 * @brief Lee un archivo introducido en la entrada estandar por el usuario
 * 
 * @param input: Archivo recibido de la entrada estandar
 * @param array_input_stdin: array del input de la entrada estandar
*/
int read_file(FILE * input, array_numbers_t* array_input_stdin);


/**
 * @brief Imprime ayuda para el usuario cuando se ingresa --help
 * 
 * @param void
*/
int print_help(void);

/**
 * @brief Se encarga de analizar argumentos si el usuario dió alguno
 * 
 * @param argc: argc dado por el usuario
 * @param argv: argv dado por el usuario
*/
int analyze_arguments(int argc, char* argv[]);

#endif  // FILE_READ_OUT_H




/**
 * @brief Imprime de la manera indicada, para numeros pares.
 *
 * Esta función busca las sumas de números primos para un número par dado en
 * una lista de números primos.
 *
 * @param arr_input_stdin ptr* array de datos ingresado por el usuario
 * @param arr_goldbach ptr* al array que contiene las sumas de números primos.
 * @param main_index index del número par en la lista arr_input_stdin
 * @param goldbach_index index actual de las sumas de números primos en 
 *  arr_goldbach.
 * @param sums_counter Contador de las sumas encontradas.
 * @return EXIT_SUCCESS si la función se ejecuta correctamente.
 */

int print_even(array_numbers_t* arr_input_stdin, array_numbers_t* arr_goldbach,
  int64_t main_index, int64_t goldbach_index, int64_t sums_counter);

/**
 * @brief Imprime de la manera indicada, para numeros impares.
 *
 * Esta función busca las sumas de números primos para un número par dado en
 * una lista de números primos.
 *
 * @param arr_input_stdin ptr* array de datos ingresado por el usuario
 * @param arr_goldbach ptr* al array que contiene las sumas de números primos.
 * @param main_index index del número par en la lista arr_input_stdin
 * @param goldbach_index index actual de las sumas de números primos en 
 *  arr_goldbach.
 * @param sums_counter Contador de las sumas encontradas.
 * @return EXIT_SUCCESS si la función se ejecuta correctamente.
 */
int print_odd(array_numbers_t* arr_input_stdin, array_numbers_t* arr_goldbach,
  int64_t main_index, int64_t goldbach_index, int64_t sums_counter);

