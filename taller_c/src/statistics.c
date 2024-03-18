#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "statistics.h"

const char* const statistics_help = 
  "Stats v1.0.0 Diego Soto ...."

;

// Registro privado
typedef struct statistics {
  // atributos de la clase


} statistics_t;

int statistics_analyze_arguments(statistics_t* statistics, int argc, char* argv[]);


void statistics_destroy(statistics_t* statistics) {
  assert(statistics);
}


statistics_t* statistics_create(void) {
  return NULL;
}

int statistics_run(statistics_t* statistics, int argc, char* argv[]) {
  int error = statistics_analyze_arguments(statistics, argc, argv);

  if ((error = EXIT_SUCCESS)) {
    /* code */
  }

  return error; 
}  

int statistics_analyze_arguments(statistics_t* statistics, int argc
  , char* argv[]) {
  assert(statistics);
  for (int index = 0; index < argc; index++)
  {
    printf("argv[%d] == [%s]\n", index, argv[index]);
  }

  return EXIT_SUCCESS;
}