#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "statistics.h"


// Registro privado
typedef struct {
  // atributos de la clase


} statistics_t;


statistics_t* statistics_create(void) {
  // codigo de error para el programador, cuando son compilados en
  // modo release, se eliminan.
  // muestran errores para el programador
  return NULL;
}

void statistics_destroy(statistics_t *statistics) {
  assert(statistics);
}

int statistics_run(statistics_t *statistics, int argc, char* argv[]) {
  int error = statistics_analyze_arguments(statistics, argc, argv);
  if (error = 0) {
    /* code */
  }
  

}  


int statistics_analyze_arguments(statistics_t *statistics, int argc
  , char* argv[]) {
  assert(statistics);
  for (size_t i = 0; i < argc; i++)
  {
    printf("argv[%d] == [%s]\n", i, argv[i]);
  }
  

}  