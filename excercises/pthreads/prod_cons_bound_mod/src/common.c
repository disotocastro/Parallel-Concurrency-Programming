#include "common.h"

#include <unistd.h>
#include <stdlib.h>

useconds_t random_between(useconds_t min, useconds_t max) {
  return min + (max > min ? (random() % (max - min)) : 0);
}