//Copyright 2024 Diego Soto <juan.sotocastro@ucr.ac.cr>

#ifndef FILE_READ_OUT_H
#define FILE_READ_OUT_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "array_numbers.h"

int read_file(FILE * input, array_numbers_t* input_file);


#endif // FILE_READ_OUT_H 