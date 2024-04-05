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

## Exclusión mutua:

## Semáforo:

Metafora del semaforo: https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/
  lecciones/0909-mutex/semaphor_metaphor.mp4


## Barrera:

## Variable de condición:

## Candado de lectura y escritura:

## Descomposición:

## Mapeo:

## Incremento de velocidad:

## Comunicación punto a punto entre procesos:

## Comunicación colectiva entre procesos:

## Reducción:




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


# Funcionamiento










## Resto del readme por defecto, puede servir para ver otras funcionalidades del Markdown
To make it easy for you to get started with GitLab, here's a list of recommended next steps.

Already a pro? Just edit this README.md and make it your own. Want to make it easy? [Use the template at the bottom](#editing-this-readme)!

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://git.ucr.ac.cr/JUAN.SOTOCASTRO/concurrente24a-diego_soto.git
git branch -M main
git push -uf origin main
```

## Integrate with your tools

- [ ] [Set up project integrations](https://git.ucr.ac.cr/JUAN.SOTOCASTRO/concurrente24a-diego_soto/-/settings/integrations)

## Collaborate with your team

- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Set auto-merge](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## Test and Deploy

Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing (SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# Editing this README

When you're ready to make this README your own, just edit this file and use the handy template below (or feel free to structure it however you want - this is just a starting point!). Thanks to [makeareadme.com](https://www.makeareadme.com/) for this template.

## Suggestions for a good README

Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.