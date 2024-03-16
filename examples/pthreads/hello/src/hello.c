// "Copyright 2021 Diego Soto"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void* greet(void* data);


int main(void) {
  // Codigo general para crear un hilo
  pthread_t thread;

  // int  pthread_create(&variable, parametro de prioridad (null defecto),
  // subturina (tarea que quiero que el hilo haga)

  int error = pthread_create(&thread, /*Parametro*/ NULL, greet, /*Args*/ NULL);
  if (error == EXIT_SUCCESS) {
    printf("Hello from main thread \n");
    pthread_join(thread, /*valor de puntero a puntero*/ NULL);
  } else {
  // archivo para reportar errores
    fprintf(stderr, "Could not create secondary thread\n");
  }
  // Manejo de errores en C con codigos de error
  return error;
}


/*
  Punteros a funciones
  void* (*start_routine) (void*);
*/

//  este valor de data es lo que yo quiero que el hilo trabaje

void* greet(void* data) {
  // para utilizar un parametro sin utilizar, no hace nada
  (void)data;
  printf("Hello from secondary thread \n");
  return NULL;
}

// https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/lecciones/0823-tools/g3/hello_impl-pthread_create-stderr.mp4
// Para compilar: cc -g -Wall -Wextra hello.c -o hello -pthread



// Solucion del ejercicio:
//https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/lecciones/0823-tools/g1/fix_thread_leak-pthread_join.mp4




