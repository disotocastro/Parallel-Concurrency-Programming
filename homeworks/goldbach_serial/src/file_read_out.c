//Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_read_out.h"

const char* const goldbach_help = 
  "Goldbach v1.0.0 by Diego Soto"
  "Usage 1: ./goldbach < [input_files.txt] \n"
  "Usage 2: ./goldbach, enter the numbers when you ready press CTRL + D \n"
  "Options:\n"
  " '-'Number, is for show the sums \n"
  " Example: -8 = 3+5 \n"
;

// Se encarga de leer el archivo
int read_file(FILE * input, array_numbers_t* input_file) {
  long long value = 0ll;

  while (fscanf(input, "lld", &value)==1) {
    // Falta agregar un menejo de excepcion aquí    
  }
  
  return EXIT_SUCCESS;
}
