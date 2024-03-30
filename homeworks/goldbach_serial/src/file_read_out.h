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
