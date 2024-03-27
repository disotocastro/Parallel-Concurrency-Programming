#ifndef ARRAY_NUMBERS_H
#define ARRAY_NUMBERS_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  size_t capacity;
  size_t count;
  int64_t* elements;
} array_numbers_t;

int array_init(array_numbers_t* array);
void array_destroy(array_numbers_t* array);
int array_append(array_numbers_t* array, int64_t element);

#endif  // ARRAY_NUMBERS_H