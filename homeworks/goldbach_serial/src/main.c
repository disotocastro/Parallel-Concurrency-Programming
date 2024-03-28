// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_read_out.h"
#include "array_numbers.h"
#include "goldbach.h"

int main() {
  FILE* input = stdin;
  array_numbers_t array_input_stdin;
  array_init(&array_input_stdin);
  read_file(input, &array_input_stdin);


  return 0;
}
