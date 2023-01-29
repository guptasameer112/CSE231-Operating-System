#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

# define N 5

sem_t forks[N];
sem_t table;

int number[N] = {0, 1, 2, 3, 4};
int numPhilosophers = N;

void thinking()
{
    sleep(1);
}

void takeForks(int philosopher)
{
    int left = (philosopher + 1) % (4 + 1);
    int right = (philosopher + 4) % (4 + 1);
    sem_wait(&forks[left]);
    sem_wait(&forks[right]);
}

void putForks(int philosopher)
{
    int left = (philosopher + 1) % (4 + 1);
    int right = (philosopher + 4) % (4 + 1);
    sem_post(&forks[left]);
    sem_post(&forks[right]);
}

void *PhiloFunction(void* philosopherNumber)
{
    for (int meals = 0; meals < 100;)
    {
        thinking();
        sem_wait(&table);
        numPhilosophers++;
        if (numPhilosophers == 4)
        {
            sem_post(&table);
        }
        takeForks(*(int *)philosopherNumber);
        printf("\nPhilosopher %d is eating", *(int *)philosopherNumber + 1);

        printf("\nPhilosopher %d is now thinking", *(int *)philosopherNumber + 1);

        thinking();
        putForks(*(int *)philosopherNumber);
        sem_post(&table);
        numPhilosophers--;
        meals++;
    }
}

int main(){
    printf("\nPhilosophers are in thinking state\n");

    sem_init(&forks[0], 0, 1);
    sem_init(&forks[1], 0, 1);
    sem_init(&forks[2], 0, 1);
    sem_init(&forks[3], 0, 1);
    sem_init(&forks[4], 0, 1);

    sem_init(&table, 0, 4);

    pthread_t Philosopher[N];
    pthread_create(&Philosopher[0], NULL, PhiloFunction, (void *) &number[0]);
    pthread_create(&Philosopher[1], NULL, PhiloFunction, (void *) &number[1]);
    pthread_create(&Philosopher[2], NULL, PhiloFunction, (void *) &number[2]);
    pthread_create(&Philosopher[3], NULL, PhiloFunction, (void *) &number[3]);
    pthread_create(&Philosopher[4], NULL, PhiloFunction, (void *) &number[4]);

    pthread_join(Philosopher[0], NULL);
    pthread_join(Philosopher[1], NULL);
    pthread_join(Philosopher[2], NULL);
    pthread_join(Philosopher[3], NULL);
    pthread_join(Philosopher[4], NULL);

    return 0;
}
