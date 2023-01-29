#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_MEALS 100

sem_t forks[NUM_PHILOSOPHERS];
sem_t table;
sem_t saucebowl;

int number[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};

void thinking(int philosopher) {
  printf("Philosopher %d is thinking\n", philosopher + 1);
  sleep(1);
}

void sitAtTable(int philosopher) {
  sem_wait(&table);
  sem_wait(&saucebowl);
}

void leaveTable(int philosopher) {
  sem_post(&saucebowl);
  sem_post(&table);
}

void takeForks(int philosopher) {
  int leftFork = philosopher;
  int rightFork = (philosopher + 1) % NUM_PHILOSOPHERS;
  sem_wait(&forks[leftFork]);
  sem_wait(&forks[rightFork]);
}

void putForks(int philosopher) {
  int leftFork = philosopher;
  int rightFork = (philosopher + 1) % NUM_PHILOSOPHERS;
  sem_post(&forks[rightFork]);
  sem_post(&forks[leftFork]);
}

void *eat(void* philosopherNumber) {
  for (int meals = 0; meals < NUM_MEALS; meals++) {
    thinking(*(int*)philosopherNumber);

    sitAtTable(*(int*)philosopherNumber);
    takeForks(*(int*)philosopherNumber);
    int bowl = rand() % 2;
    printf("Philosopher %d is eating from bowl %d\n", *(int*)philosopherNumber + 1, bowl + 1);

    putForks(*(int*)philosopherNumber);
    leaveTable(*(int*)philosopherNumber);
  }
}

int main() {
  printf("Philosophers are in thinking state\n");

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_init(&forks[i], 0, 1);
  }
  
  sem_init(&table, 0, NUM_PHILOSOPHERS - 1);
  sem_init(&saucebowl, 0, 2);

  pthread_t Philosopher[NUM_PHILOSOPHERS];
  int philosopherNumbers[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};
    pthread_create(&Philosopher[0], NULL, eat, (void *) &number[0]);
    pthread_create(&Philosopher[1], NULL, eat, (void *) &number[1]);
    pthread_create(&Philosopher[2], NULL, eat, (void *) &number[2]);
    pthread_create(&Philosopher[3], NULL, eat, (void *) &number[3]);
    pthread_create(&Philosopher[4], NULL, eat, (void *) &number[4]);

    pthread_join(Philosopher[0], NULL);
    pthread_join(Philosopher[1], NULL);
    pthread_join(Philosopher[2], NULL);
    pthread_join(Philosopher[3], NULL);
    pthread_join(Philosopher[4], NULL);

}