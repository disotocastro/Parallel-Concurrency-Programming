// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_read_out.h"

const char* const goldbach_help =
  "Goldbach v1.0.0 by Diego Soto\n"
  "Usage 1: ./goldbach_serial < [input_files.txt] \n"
  "Usage 2: ./goldbach_serial, enter the numbers, when you ready press CTRL + D \n"
  "Options:\n"
  " '-'Number, is for show the sums \n"
  " Example: -8 = 3+5 \n\n";

// Se encarga de leer el archivo
int read_file(FILE * input, array_numbers_t* input_file) {
  int64_t value = 0ll;
  printf("=== Golbach Serial === \nIf you're ready, press: CTRL + D\n");
  printf("For more info, enter: ./golbach_serial --help\n");
  printf("Numbers to test: \n");
  // falta agregar correcion de erorres
  while (fscanf(input, "%ld", &value) == 1) {
    array_append(input_file, value);
  }
  printf("\n");
  return EXIT_SUCCESS;
}

int print_help(void) {
  printf("%s", goldbach_help);
  return EXIT_SUCCESS;
}

int analyze_arguments(int argc, char* argv[]) {
  for (int index = 1; index < argc; index++) {
    if ( strcmp(argv[index], "--help") == 0 ) {
      print_help();
      break;
    } 

    else if (*argv[index] == '-'){
      fprintf(stderr, "error: unknow option: %s\n", argv[index]);
      return  EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}