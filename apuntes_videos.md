# Rastreo de memoria. Cargado del proceso. Segmento de código. Segmento de datos

- Para cargar un proceso, cuando un ejecutable se abre, el un segmento del codigo
 se copia en memoria principal a esto se le llama "segmento del codigo"

- El segmento de datos, tambien viene del ejecutable y se copia exactamente igual
aqui se encuentran las variables de manera estatico (alojamiento estatico static)
static proboca que se cargue en el segmento de datos y no en la invocacion de la rutina

- Las variables globales son malas practicas de programacion en el mundo serial, pero
en el mundo concurrente son HORRIBLES. NO usar, prohibidas en el curso. 

## Creación del hilo principal. El ambiente de ejecución del lenguaje (crt0)

- Cuando el sistema operativo crea el hilo principal, va a ejecutar
la libreria de C, Runtime Library o Crt0. Esta funcion localiza la funcion Main 
y ejecuta la accion.

## Invocación de main(). Stack frame

- Stack frame: Region de la memoria donde se colocan variables globales de la
invocacion de una subrutina.


## Colas de archivos
- Una cola utiliza memoria discontinua