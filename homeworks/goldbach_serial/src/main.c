// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>


#include "file_read_out.h"
#include "array_numbers.h"
#include "goldbach.h"

int main() {
  FILE* input = stdin;
  array_numbers_t arr_input_stdin;
  array_init(&arr_input_stdin);
  read_file(input, &arr_input_stdin);

  int64_t largest_element = largest_element_arr(&arr_input_stdin);
  printf("largest element in the array: %" PRId64 "\n", largest_element);
  return 0;
}
