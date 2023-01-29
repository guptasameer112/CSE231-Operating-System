#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

# define N 5

sem_t forks[N];

int saucebowl[2] = {1, 1};
int state[N] = {1, 1, 1, 1, 1};
int number[N] = {0, 1, 2, 3, 4};

void thinking()
{
    sleep(1);
}

void takeForks(int philosopher)
{
    if (philosopher % 3 == 0)
    {
        int left = (philosopher + 1) % (4 + 1);
        int right = (philosopher + 4) % (4 + 1);
        sem_wait(&forks[philosopher]);
        sem_wait(&forks[left]);
    }
    else
    {
        int left = (philosopher + 1) % (4 + 1);
        int right = (philosopher + 4) % (4 + 1);
        sem_wait(&forks[left]);
        sem_wait(&forks[philosopher]);
    }
}

void putForks(int philosopher)
{
    if (philosopher % 3 == 0)
    {
        int left = (philosopher + 1) % (4 + 1);
        int right = (philosopher + 4) % (4 + 1);
        sem_post(&forks[philosopher]);
        sem_post(&forks[left]);
    }
    else
    {
        int left = (philosopher + 1) % (4 + 1);
        int right = (philosopher + 4) % (4 + 1);
        sem_post(&forks[left]);
        sem_post(&forks[philosopher]);
    }
}

void *PhiloFunction(void* philosopherNumber)
{
    for (int meals = 0; meals < 100;)
    {
        thinking();

        takeForks(*(int *)philosopherNumber);
        int bowl = rand() % 2;
        saucebowl[bowl] = 0;
        printf("\nPhilosopher %d is eating from bowl %d", *(int *)philosopherNumber + 1, bowl + 1);
        state[*(int *)philosopherNumber] = 0;
       
        printf("\nPhilosopher %d is now thinking", *(int *)philosopherNumber + 1);
        state[*(int *)philosopherNumber] = 1;
        saucebowl[bowl] = 1;

        thinking();
        putForks(*(int *)philosopherNumber);

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


    pthread_t Philosopher[5];

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

}
