#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUMBER_SHOTS 3

pthread_t* create_team(int athlete_count);
void* shot_put1(void* data);
void* shot_put2(void* data);

int main(int argc, char const *argv[]) {


  int error = EXIT_SUCCESS;
  int error_call_team1 = EXIT_SUCCESS;
  int error_call_team2 = EXIT_SUCCESS;

  uint64_t athlete_count = 0;
  int64_t score_t1 = 0;
  int64_t score_t2 = 0;

  void* best_shot1 = 0;
  void* best_shot2 = 0;
  
  //uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);

  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &athlete_count) == 1) {
      if ((athlete_count % 2) != 0){
        // Camino Feliz...
      } else {
        fprintf(stderr, "Error: Athlete count must be odd\n");
        return EXIT_FAILURE;
      }
    } 
  } else{
    fprintf(stderr, "Error: Please a valid format: ./team_shot_put [ N ]] \n");
    return EXIT_FAILURE;
  }

  //...Camino Feliz
  // Seguidamente crean dos equipos de la misma cantidad de atletas
  pthread_t* th_team1 = (pthread_t*) malloc(athlete_count * sizeof(pthread_t));
  pthread_t* th_team2 = (pthread_t*) malloc(athlete_count * sizeof(pthread_t));


// TODO: Seprar el for en 2 para terminar la concurrencia
  if (th_team1 && th_team2) 
  {
    // EQUIPO 1, creacion de hilos
    for (uint64_t thread_number = 0; thread_number < athlete_count
    ; ++thread_number) 
    {

      error_call_team1 = pthread_create(&th_team1[thread_number], NULL
       ,shot_put1, (void*) thread_number);

      if (error_call_team1 == EXIT_SUCCESS) {
        // Se crea um join
        pthread_join(th_team1[thread_number], &best_shot1);

      } else {
        fprintf(stderr, "Error: Could not create that number of Athletes \n");
        error_call_team1 = 21;
        break;
      }

      error_call_team2 = pthread_create(&th_team2[thread_number], NULL
       ,shot_put2, (void*) thread_number);

      if (error_call_team2 == EXIT_SUCCESS) {
        // Se crea um join
        pthread_join(th_team2[thread_number], &best_shot2);

      } else {
        fprintf(stderr, "Error: Could not create that number of Athletes \n");
        error_call_team2 = 21;
        break;
      }


        
      // Cast a double de las mejores puntuaciones
      double dbest_shot1 = *((double*) best_shot1);
      double dbest_shot2 = *((double*) best_shot2);

      // Sumador de puntos, arbitro !!
      if ( dbest_shot1 > dbest_shot2 ) {
        score_t1+=1;
      } else{
        score_t2+=1;
      }

      free(best_shot2);
      free(best_shot1);

    }

  } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64 " Athletes\n"
      , athlete_count);
    error = 22;
  }


  
    // imprimir ganador

    printf("Final score: Team 1: %" PRId64, score_t1);
    printf(" vs Team 2: %" PRId64 "\n", score_t2);

    if (score_t1 > score_t2) {
      printf("Winner: Team 1\n");
    } else {
      if (score_t1 < score_t2) {
        printf("Winner: Team 2\n");
      } else {
        printf("Draw!!\n");
      }
    }

      free(th_team1);
      free(th_team2);

  return error;
}

// Aquí se crea un equipo dinamico, cada equipo cuenta con una cantidad
// de punteros igual 
// Create_Team es un creador de hilos dinamico
pthread_t* create_team(int athlete_count) {

  pthread_t* athletes = (pthread_t*) calloc(athlete_count, sizeof(pthread_t));
  if (athletes) {
    return athletes;
  } else {
        fprintf(stderr, "Error: Could not create the team \n");
    return NULL;
  }
}

// TODO: Agregar if mejorar la robuste el programa
// TODO: Pensar una forma de hacerlo sin necesitar 2 funciones distintas de shot

void* shot_put1(void* data) {
  int64_t id = (int64_t)data;

  // clock_gettime() permite obtener un tiempo en nanosegundos, es usado
  // para generar una mejor seed.
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  unsigned int seed = (unsigned int)(ts.tv_nsec ^ id);

  double* shots = (double*)calloc(NUMBER_SHOTS, sizeof(double));

  // Se le asignan los valores a los disparos
  for (int i = 0; i < NUMBER_SHOTS; i++) {
    shots[i] = (double)(rand_r(&seed) % (10 * 25) + 1) / 10.0;
  }

  // Se busca el mejor disparo
  double* best_shot = (double*)calloc(1, sizeof(double));
  *best_shot = shots[0];
  for (int i = 1; i < NUMBER_SHOTS; i++) {
    if (shots[i] > *best_shot) {
      *best_shot = shots[i];
    }
  }

  printf("1.%ld best shot put %.3fm\n", id + 1, *best_shot);
  free(shots);
  return best_shot;
}

void* shot_put2(void* data) {
  int64_t id = (int64_t)data;

  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  unsigned int seed = (unsigned int)(ts.tv_nsec ^ id);

  double* shots = (double*)calloc(NUMBER_SHOTS, sizeof(double));

  for (int i = 0; i < NUMBER_SHOTS; i++) {
    shots[i] = (double)(rand_r(&seed) % (10 * 25) + 1) / 10.0;
  }

  double* best_shot = (double*)calloc(1, sizeof(double));
  *best_shot = shots[0];
  for (int i = 1; i < NUMBER_SHOTS; i++) {
    if (shots[i] > *best_shot) {
      *best_shot = shots[i];
    }
  }

  printf("2.%ld best shot put %.3fm\n", id + 1, *best_shot);
  free(shots);
  return best_shot;
}
