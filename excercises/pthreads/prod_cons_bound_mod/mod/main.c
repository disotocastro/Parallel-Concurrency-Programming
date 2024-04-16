#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;

  simulation_t* simulation = simulation_create();

  if (simulation) {
    error = simulation_run(simulation, argc, argv);
    simulation_destroy(simulation);
  } else {
    fprintf(stderr, "error: could not allocate simulation\n");
    error = EXIT_FAILURE;
  }
  
  return error;
}