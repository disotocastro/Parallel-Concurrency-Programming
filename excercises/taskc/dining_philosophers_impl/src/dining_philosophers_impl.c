#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THINKING 2
#define HUNGRY 1
#define EATING 0

typedef struct monitor {
    int N; // Number of philosophers
    int* state; // Estado del Filosofo 
    pthread_cond_t* phcond; // Philosopher condition variable
    pthread_mutex_t mutex; // Mutex variable for synchronization
    int times; // Number of iterations
    int* meals; // Number of meals eaten by each philosopher
} monitor_t;

typedef struct private_data {
    int phnum;
    monitor_t* monitor;
} private_data_t;

void monitor_init(monitor_t* monitor, int N, int times);
void monitor_destroy(monitor_t* monitor);
void test(monitor_t* monitor, int phnum);
void take_fork(monitor_t* monitor, int phnum);
void put_fork(monitor_t* monitor, int phnum);
void* philosopher(void* arg);
void print_meals_eaten(monitor_t* monitor);

int main() {
    int n_philosophers = 0;
    printf("Please, enter the number of philosophers: ");
    scanf("%d", &n_philosophers);

    if (n_philosophers <= 0) {
        fprintf(stderr, "Number of philosophers must be greater than 0\n");
        return EXIT_FAILURE;
    }

    monitor_t monitor;   //   n          times
    monitor_init(&monitor, n_philosophers, 30);

    // Create philo threads
    pthread_t* thread_id = (pthread_t*)malloc(n_philosophers * sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*)malloc(n_philosophers * 
      sizeof(private_data_t));

    for (int i = 0; i < n_philosophers; i++) {
        private_data[i].phnum = i;
        private_data[i].monitor = &monitor;
        pthread_create(&thread_id[i], NULL, philosopher, &private_data[i]);
        printf("Philosopher %d is thinking...\n", i + 1);
    }

    // Join threads
    for (int i = 0; i < n_philosophers; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Print meals eaten
    print_meals_eaten(&monitor);

    free(thread_id);
    free(private_data);
    monitor_destroy(&monitor);
    return 0;
}

void test(monitor_t* monitor, int phnum) {
  if (monitor->state[(phnum + 1) % monitor->N] != EATING &&
    monitor->state[(phnum + monitor->N - 1) % monitor->N] != EATING &&
    monitor->state[phnum] == HUNGRY) {
    monitor->state[phnum] = EATING;
    monitor->meals[phnum]++; // Increment meals eaten
    pthread_cond_signal(&monitor->phcond[phnum]);
  }
}

void take_fork(monitor_t* monitor, int phnum) {
  pthread_mutex_lock(&monitor->mutex);
    monitor->state[phnum] = HUNGRY;
    test(monitor, phnum);
    if (monitor->state[phnum] != EATING) {
        pthread_cond_wait(&monitor->phcond[phnum], &monitor->mutex);
    }
    printf("Philosopher %d is Eating\n", phnum + 1);
  pthread_mutex_unlock(&monitor->mutex);
}

void put_fork(monitor_t* monitor, int phnum) {
  pthread_mutex_lock(&monitor->mutex);
    monitor->state[phnum] = THINKING;
    test(monitor, (phnum + 1) % monitor->N);
    test(monitor, (phnum + monitor->N - 1) % monitor->N);
  pthread_mutex_unlock(&monitor->mutex);
}

void monitor_init(monitor_t* monitor, int N, int times) {
  monitor->N = N;
  monitor->times = times;
  monitor->state = (int*)malloc(N * sizeof(int));
  monitor->phcond = (pthread_cond_t*)malloc(N * sizeof(pthread_cond_t));
  monitor->meals = (int*)calloc(N, sizeof(int)); // Initialize meals eaten to 0

  for (int i = 0; i < N; i++) {
    monitor->state[i] = THINKING;
    pthread_cond_init(&monitor->phcond[i], NULL);
  }
  pthread_mutex_init(&monitor->mutex, NULL);
}

void monitor_destroy(monitor_t* monitor) {
  for (int i = 0; i < monitor->N; i++) {
    pthread_cond_destroy(&monitor->phcond[i]);
  }
  pthread_mutex_destroy(&monitor->mutex);
  free(monitor->state);
  free(monitor->phcond);
  free(monitor->meals);
}

void* philosopher(void* arg) {
    private_data_t* data = (private_data_t*)arg;
    int phnum = data->phnum;
    monitor_t* monitor = data->monitor;
    int meals_eaten = 0;
    while (meals_eaten < monitor->times) {
      sleep(1);
      take_fork(monitor, phnum);
      sleep(0.5);
      put_fork(monitor, phnum);
      meals_eaten = monitor->meals[phnum];
    }
    return NULL;
}

void print_meals_eaten(monitor_t* monitor) {
    printf("Meals eaten by each philosopher:\n");
    for (int i = 0; i < monitor->N; i++) {
      printf("Philosopher %d: %d meals\n", i + 1, monitor->meals[i]);
    }
}
