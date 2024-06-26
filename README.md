# concurrente24a-diego_soto

# Glosario

## Programación serial:
Tareas que se ejecutan de de manera secuencial, siguiendo el orden especifico con el que fueron programadas.

## Programación concurrente:
Todo lo que no es serial, las tareas se van intercalando. Se está haciendo una cosa y de repente cambia a hacer otra.
 
## Programación paralela:
Las tareas se están realizando al mismo tiempo, de manera simultanea. El paralelismo es una forma de concurrencia.

## Concurrencia de tareas:
Separación de problemas (diferentes ejecutantes hacen diferentes tareas)

### Recursos mono-hilo: call-back, async/await:

### Call-back: 
Manejo de eventos, los eventos son cosas que no se saben cuando van a pasar. 
### Async/Await:
Forma de programar que utiliza JS para programar de manera concurrente, su código puede llegar a parecer de manera serial.

### Compartidos multi-hilo: Pthreads, OpenMP: 
Multiples ejecutantes en un ambiente de recursos compartidos. Los ejecutantes multi-hilo se comparten información (estado de memoria, recursos, estado) sin
necesidad de un tercero (sistema operativo), no hay que solicitarle al OS algo para que esto suceda. 
#### Pthreads:
Tecnología que nos permite crear hilos de ejecución, controlarlos a nuestro gusto. Concurrencia procidemental.
#### OpenMP:
Solo sirve para un subconjunto, cierto tipo de problemas, más declarativo. Un poco más funcional. 
### Recursos distribuidos simetricamente: Clusters 
Todas las máquinas son lo más similares entre ellas, comparten las mismas especificaciones en TODO. Estos son clusters de computadoras. 
MPI: Interfaz de Paso de Mensajes: Mecanismo para comunicar ejecutantes que distribuyen recursos. Pueden esta en la misma maquina pero no comparten recursos.

### Recursos distribuidos asimétricamente: Mallas
Distantas oficinas de trabajo, una en CR y otra en Madrid. Se necesita invervención del sistema operativo. La comunicación es más limitada y lenda.

Los recursos no son simetricos, los recursos tienen que correr en muchos tipos de hardware distinto (Malla).
EJ: Desarrollar una aplicación para Android, recompilarla para IOS y luego tmb para PC... 

### Acelerador: Heterogéneo multiproceso
Combinación de recursos compartidos con recursos distribuidos.
Dispositivos optimizados para un cierto problema (EJ: Tarjetas de video)
Aquí se consiguen los mejores resultados.
Las intrucciones están divididos para el CPU y el GPU. Dos segmentos de código en el mismo programa, el CPU llama al GPU a ir realizando cierta tarea
Mientras el CPU continua haciendo otras tareas y espera el resultado del GPU.


## Paralelismo de datos:
Su objetivo es el incremento del desempeño, tiene que ver con el High Performance Computers


## Rastreo de memoria:
Correr el programa e ir creando evidencia de lo que va pasando en el programa
Se rastrean 3 recursos
- Memoria
- Procesamiento
- Comunicación 

## Hilo de ejecución:
Un arreglo de valores que el OS carga en los registros de una CPU y permiten
ejecutar código en esa CPU.

## Indeterminismo:
La concurrencia genera indetermismo, eso es que uno no puede predecir el orden
en el que se van a ejecutar las condiciones concurrentes.
Cuando se tiene concurrencia, naturalmente está el indeterminismo.

Sino hay indeterminismo, esto puede ser serial. Concurrente es lo que no es
serial. 
 

## Memoria privada y compartida:
### Privada
Memoria que un hilo tiene y otro hilo no, esta no se altea por los cambios
que yo le haga a la memoria de otro hilo, se crea haciendo un struct.

## Espera activa:
La espera activa (busy waiting) es un ciclo que hace a un hilo de ejecución
esperar repetitivamente hasta que una condición se haga falsa

## Condición de carrera:
Es cuando dos hilos están peleando por un mismo recurso. Modicación concurrente
de memoria compartida. 

## Control de concurrencia:
Si dos hilos intentan escribir en el mismo archivo, el primero que llegó escribe
y el otro espera. Se definirará mejor más adelante.

## Seguridad condicional:
Darle a un solo hilo el trabajo de impresión, mientras que el resto de hilos
se encargan del resto del trabajo computacional, permitiendo un orden en la 
salida

## Exclusión mutua:

## Semáforo:
Metafora del semaforo: https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/
  lecciones/0909-mutex/semaphor_metaphor.mp4


## Barrera:
Tipo de sincronización entre hilos o procesos, donde todos los participantes 
deben alcanzar un punto específico del programa antes de que cualquiera pueda seguir.

## Variable de condición:
Mecanismo de sincronización que permite a los  hilos esperar (bloquearse) hasta 
que una condición particular se cumpla. Se utiliza en combinación con cerrojos (locks) 
y permite que los hilos esperen de manera eficiente por ciertas condiciones sin consumir CPU.

## Candado de lectura y escritura:
(Read-Write Lock) permite un mayor grado de concurrencia que un simple mutex. 
Permite que múltiples hilos lean un recurso compartido simultáneamente, pero solo 
un hilo puede escribir en el recurso a la vez. Esto mejora el rendimiento en 
situaciones donde las operaciones de lectura son más frecuentes que las de escritura.

## Descomposición:
Se refiere a dividir un problema en partes más pequeñas que pueden ser ejecutadas 
concurrentemente. Puede ser de dos tipos: descomposición de datos, 
donde los datos se dividen entre los hilos, y descomposición de tareas, 
donde las tareas o funciones se dividen entre los hilos.

## Mapeo:
Diferentes formas de asignar las de tareas o datos a diferentes hilos o procesos.
Con el fin de conseguir un aumento de eficiencia.

## Incremento de velocidad:
Se refiere a la mejora en el rendimiento de un programa concurrente en 
comparación con su versión serial. Se mide generalmente por la relación entre 
el tiempo de ejecución serial y el tiempo de ejecución paralelo, conocido como 
speedup. Un incremento de velocidad ideal es lineal, pero en la práctica, 
suele estar limitado por factores como la sobrecarga de comunicación 
y la ley de Amdahl.

## Comunicación punto a punto entre procesos:
Es un método de comunicación en el que los datos se transfieren directamente 
entre dos procesos. Este tipo de comunicación es fundamental en sistemas 
distribuidos y concurrentes, y se implementa comúnmente utilizando sockets, 
pipes o mecanismos de paso de mensajes como MPI (Message Passing Interface).

## Comunicación colectiva entre procesos:
Forma de comunicación en la que un grupo de procesos participa en la 
transferencia de datos. Incluye operaciones como difusión (broadcast), 
reducción (reduce), y barrera (barrier), y es común en entornos de computación 
paralela y distribuida, utilizado en MPI.

## Reducción:
Es una operación colectiva en programación paralela donde se combinan 
los valores de todas las tareas o procesos para producir un único resultado.
Se usa comúnmente en operaciones como sumas, productos, máximos y mínimos, 
y se utiliza en MPi.


# Otras definiciones importantes:

## Record
Registro de memoria, region de la memoria de archivos del mismo tipo
cuyo valor de cada dato puede variar -> [64bits, 32bits, 32bits, , 64its]
## Malloc 
Inicializa el espacio en memoria, pero no le pone nada, es mas rapido
Reserva 20 megas de memoria y lo deja ahi, siempre tiene basura
## Calloc 
Inicializa el espacio en memoria y ademas la inicializa en 0, mas lento
Se utiliza para hacer vectores
## HPC
  High Performance Computers  
## Linter o Lint
Del ingles "Pelusa" quita cosas indeseables en el codigo
para usarlo: cpplint prueba.c

## valgrind -> memcheck
Corre codigo de cualquier programa, solo se necesita el ejecutable
valgrind --leak-check=full ./prueba


## Sanitazers: Necesitan codigo fuente
## Asan 
Invalid access and memory leaks
## msan
Unintialized memory
## tsan
Thread sanitazer
## ubsan
Undefined behavior
