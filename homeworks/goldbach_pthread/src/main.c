// Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_read_out.h"
#include "array_numbers.h"
#include "goldbach.h"
#include "concurrency.h"

int main(int argc, char* argv[]) {

  golbach_concurrency(argc, argv);
  
  return EXIT_SUCCESS;
}
