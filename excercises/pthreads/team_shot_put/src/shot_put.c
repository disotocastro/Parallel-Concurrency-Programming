#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>

#define MAX_DISTANCE 25
#define MAX_TEAMS 2
#define MAX_SHOTS 3

int create_team(uint64_t athlete_count);
void* shots(void* data);


int main(int argc, char const *argv[]) {
  
  int error = EXIT_SUCCESS;
  uint64_t athlete_count = 0;

  //uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);

  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &athlete_count) == 1) {
      if ((athlete_count % 2) != 0){
        // Camino Feliz
      } else {
        fprintf(stderr, "Error: Athlete count must be odd\n");
        return EXIT_FAILURE;
      }
    } 
  } else{
    fprintf(stderr, "Error: Please a valid format -> ./team_shot_put Number \n");
    return EXIT_FAILURE;
  }


  error = create_team(athlete_count);
  return error;
}

// Aquí se crea un equipo dinamico, cada equipo cuenta con una cantidad
// de punteros igual 
// Create_Team es un creador de hilos dinamico

int create_team(uint64_t athlete_count) {
  int error = EXIT_SUCCESS;

  // Se crea X cantidad de hilos para la N cantidad de atletas
  pthread_t* threads = (pthread_t*) malloc(athlete_count * sizeof(pthread_t));

  if (threads) {
    // Camino Feliz, se crea un hilo para cada atleta
    for (uint64_t thread_number = 0; thread_number < athlete_count
        ; ++thread_number) {
      error = pthread_create(&threads[thread_number], /*attr*/ NULL, shots
        , /*arg*/ (void*) thread_number);

      if (error == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "Error: Could not create that number of Athletes \n");
        error = 21;
        break;
      }
    }

    printf("Empiezan los balazos !!\n");

    // Liberar los hilos de manera dinamica
    for (uint64_t thread_number = 0; thread_number < athlete_count
        ; ++thread_number) {
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }
    free(threads);

  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64 " Athletes\n"
      , athlete_count);
    error = 22;
  }

  return error;
}

void* shots(void* data) {

  const uint64_t rank = (uint64_t) data;
  // print "Hello from secondary thread"
  printf("Hello from secondary thread %" PRIu64 "\n", rank);




  return NULL;
} 