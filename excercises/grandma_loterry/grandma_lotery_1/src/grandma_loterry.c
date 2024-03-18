#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

void* gen_rnumber(void* seed);

int main(void) {
  // generar la semilla con la biblioteca time.h
  unsigned int seed = time(NULL);  

  pthread_t thread1, thread2;
  int call_thread1 = pthread_create(&thread1, NULL, gen_rnumber, &seed);
  int call_thread2 = pthread_create(&thread2, NULL, gen_rnumber, &seed);
  
  if (call_thread1 == EXIT_SUCCESS && call_thread2 == EXIT_SUCCESS) {
    int* rnumber1;
    int* rnumber2;

    pthread_join(thread1, (void*)&rnumber1);
    pthread_join(thread2, (void*)&rnumber2);

    printf("Number from Thread1: %d\n", *rnumber1);
    printf("Number from Thread2: %d\n", *rnumber2);

    // Ya que se utilizo malloc:
    free(rnumber1);
    free(rnumber2);
  } else {
      // Reporte de errores
      fprintf(stderr, "Error while creating threads\n");
  }
  return EXIT_SUCCESS;

}


void* gen_rnumber(void* seed) {

  /*
    Hay que generar una semilla unica para cada hilo ya 
    que si esto no es así, si el programa se ejecuta muchas 
    veces seguidas en el mismo segundo, las ejecuciones pueden 
    dar los mismos resultados
  */

  // Obtener la semilla base, basada en el tiempo
  unsigned int* base_seed = (unsigned int*)seed;

  // Obtener el ID de cada hilo
  // man pthread_self -> obtain ID of the calling thread
  unsigned int thread_id = (unsigned int)pthread_self();

  // multiplicar la semilla por el id del hilo,
  // obteniendo un valor único para cada hilo
  unsigned int unique_seed = *base_seed * thread_id;

  // Puntero que apunta al bloque de memoria asignado por malloc
  int* rnumber = (int*)malloc(1 * sizeof(int));

  if (rnumber) {
    *rnumber = rand_r(&unique_seed) % 100;
    return (void*)rnumber;
  } else {
    fprintf(stderr, "Error while generating random number\n");
    return NULL; // EXIT_FAILURE tira warning por ser void*
  }

}