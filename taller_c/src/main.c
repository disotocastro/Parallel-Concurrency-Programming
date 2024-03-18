#include <stdio.h>
#include <stdlib.h>
#include <statistics.h>

int main(int argc, char *argv[])
{
  int error = EXIT_SUCCESS;

  statistics_t* statistics = statistics_create();

  // Codigo similar a un try catch en el main
  if (statistics) {
  
    error = statistics_run(statistics, argc, argv);
    statistics_destroy(statistics);
   
  } else{
    fprintf(stderr, "error: could not allocate statistics object \n");
  }

  return error;
}

