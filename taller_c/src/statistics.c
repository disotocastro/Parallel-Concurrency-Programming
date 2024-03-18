#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "statistics.h"

const char* const statistics_help = 
  "Stats v1.0.0 Diego Soto ...."
  "Stats v1.0.0 Diego Soto ...."
  "Stats v1.0.0 Diego Soto ...."
;

// Registro privado
typedef struct statistics {
  // atributos de la clase
  bool help_asked; 
} statistics_t;

int statistics_analyze_arguments(statistics_t* statistics, int argc, char* argv[]);

int statistics_print_help(void);


void statistics_destroy(statistics_t* statistics) {
  assert(statistics);
  free(statistics);
}


statistics_t* statistics_create(void) {

  statistics_t* statistics = (statistics_t*) 
    calloc(1, sizeof(statistics_t) );
    if (statistics){
      /* code */
    }
    
  return statistics;
}

int statistics_run(statistics_t* statistics, int argc, char* argv[]) {
  int error = statistics_analyze_arguments(statistics, argc, argv);

  if ((error == EXIT_SUCCESS)) {
    if (statistics->help_asked) {
      return statistics_print_help();
    }
  }

  return error; 
}  

int statistics_analyze_arguments(statistics_t* statistics, int argc
  , char* argv[]) {
  assert(statistics);
  // se incializa en 1 porque nos interesan los arguementos del usurio, no 
  // el nombre del programa
  for (int index = 1; index < argc; index++) {
 
    printf("argv[%d] == [%s]\n", index, argv[index]);

    // Si es == 0, es que son iguales
    if ( strcmp(argv[index], "--help") == 0) {
      statistics->help_asked = true;
      break;
    }  
  }

  return EXIT_SUCCESS;
}


int statistics_print_help(void) {
  printf("%s", statistics_help);
  return EXIT_SUCCESS;
}