#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "statistics.h"
#include "array_double.h"

const char* const statistics_help = 
  "Stats v1.0.0 Diego Soto"
  "Usage: stats [-b] [Files]\n"
  "Options:\n"
  " -b Data is binary \n"
;


// Estructura de datos cola
typedef struct statistics_file{
  const char* filename;
  struct statistics_file* next;

}statistics_file_t;

 

// Registro privado
typedef struct statistics {
  // atributos de la clase
  bool help_asked; 
  bool binary_file; 
  size_t file_count;

  // Si hago un archivo normal, es memoria continua
  // En cambio, si lo hago con punteros es memoria discontinua
  statistics_file_t* files_head;
  statistics_file_t* files_tail;
  array_double_t values; 



} statistics_t;

int statistics_analyze_arguments(statistics_t* statistics, int argc, char* argv[]);

int statistics_print_help(void);

int statistics_enqueue_file(statistics_t* statistics, const char* filename);
int statistics_analyze_file(statistics_t* statistics, FILE* file);

void statistics_print(const statistics_t* statistics);



void statistics_destroy(statistics_t* statistics) {
  assert(statistics);

  for(statistics_file_t* current = statistics->files_head; current; 
      current = statistics->files_head) {
    statistics->files_head = current->next;
    free(current);
  }
  array_double_init(&statistics->values);
  free(statistics);
}


statistics_t* statistics_create(void) {

  statistics_t* statistics = (statistics_t*) 
    // calloc inicializa la memoria en 0
    // practicamente hace que todo nuestro if sea inutil xd
    calloc(1, sizeof(statistics_t) );
    if (statistics){
      statistics->help_asked = false;
      statistics->binary_file = false;
      statistics->files_head = NULL;
      statistics->files_tail = NULL;
      statistics->file_count = 0;
      array_double_init(&statistics->values);

    }
    
  return statistics;
}

int statistics_run(statistics_t* statistics, int argc, char* argv[]) {
  int error = statistics_analyze_arguments(statistics, argc, argv);

  if ((error == EXIT_SUCCESS)) {
    if (statistics->help_asked) {
      return statistics_print_help();
    }

    if (statistics->file_count > 0) {
      for(statistics_file_t* current = statistics->files_head; current; 
          current = current->next) {
        const char* filename = current->filename;

                                            //read binary, read text
        const char* open_mode = statistics->binary_file ? "rb" : "rt";
        FILE* file = fopen(filename, open_mode);

        if (file) {
          printf("Processing... %s\n", filename);
          statistics_analyze_file(statistics, file);
          fclose(file);
        } else {
          fprintf(stderr, "error> could not open %s\n", filename);
          error = 20;
          // break ?, si se hace se detiene por compelto
        }
     } 
    } else {
      if (statistics->binary_file){
        freopen("", "rb", stdin);
      }
      statistics_analyze_file(statistics, stdin);
      printf("Processing stdin\n");
    }
  
  }


  if (error == EXIT_SUCCESS) {
    statistics_print(statistics);
  }
  


  

  return error; 
}  

int statistics_analyze_arguments(statistics_t* statistics, int argc
  , char* argv[]) {
  assert(statistics);
  // se incializa en 1 porque nos interesan los arguementos del usurio, no 
  // el nombre del programa
  for (int index = 1; index < argc; index++) {
 

    // Si es == 0, es que son iguales
    if ( strcmp(argv[index], "--help") == 0 ) {
      statistics->help_asked = true;
      break;
    } 

    // Comparacion de archivos binarios
    if ( strcmp(argv[index], "-b") == 0 ) {
      printf("argv[%d] == [%s]\n", index, argv[index]);
      statistics->binary_file = true;
    // el puntero es una desreferenciacion, basicamnete es como
    // hacer *argv[index] == argv[index][0]
    } else if (*argv[index] == '-'){ // argv[index][0]
      fprintf(stderr, "error: unknow option: %s\n", argv[index]);
      return  EXIT_FAILURE;
    } else{
      statistics_enqueue_file(statistics, argv[index]);
    }
  }

  return EXIT_SUCCESS;
}


int statistics_print_help(void) {
  printf("%s", statistics_help);
  return EXIT_SUCCESS;
}


int statistics_enqueue_file(statistics_t* statistics, const char* filename) {
  assert(statistics);
  // Si es nulo significa que esta vacio
  // se crea un nodo vacio con calloc para q empiece en 0
  statistics_file_t* node =(statistics_file_t*) 
    calloc(1, sizeof(statistics_file_t));

  if (node) {
    node->filename = filename;
    
    // Si la cola esta vacia 
    if (statistics->files_head == NULL) {
      statistics->files_head = node; 
      statistics->files_tail = node;
    } else {
      // de lo contrario, es que si hay elementos
      statistics->files_tail->next = node;
      statistics->files_tail = statistics->files_tail->next;
    }
    ++ statistics->file_count;
    return EXIT_SUCCESS;
  } else{
      fprintf(stderr, "error: couldnt create node ");
      return EXIT_FAILURE;
  } 
}

int statistics_analyze_file(statistics_t* statistics, FILE* file) {
  assert(statistics);
  assert(file);
  int error = EXIT_SUCCESS;

  double value = 0.0;
  if (statistics->binary_file){
    // formato del freal
    // &value = donde escribo
    //sizeof(double) el tamanio
    // cuantos elementos = 1,
    // archivo = file
    while (fread(&value, sizeof(double),1,file) == 1) {
      array_double_append(&statistics->values, value);

      if (error) {
        break;
      }
      

      printf("value = %lf\n", value);

    }
  } else{
    //FILE* output = fopen("output001.bin", "wb");
    while (fscanf(file,"%lf", &value) == 1){
      error = array_double_append(&statistics->values, value);
      
      if (error) {
        break;
      }

      //printf("value = %lf\n", value);
      //fwrite(&value, sizeof(value),1, output);
    }
    //fclose(output);
  }
  return error;
}

void statistics_print(const statistics_t* statistics) {
  assert(statistics);
  for (size_t i = 0; i < statistics->values.count; i++){
    const double value =  statistics->values.elements[i];
    printf("value %zu = %lf\n", i, value);
  }
  
}
