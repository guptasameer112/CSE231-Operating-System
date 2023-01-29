#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

# define N 5

pthread_mutex_t forks[N];
pthread_cond_t cond[N];

int state[N] = {1, 1, 1, 1, 1};
int number[N] = {0, 1, 2, 3, 4};

void thinking()
{
    sleep(1);
}

void takeForks(int philosopher)
{
    pthread_mutex_lock(&forks[philosopher]);
    int fork = (philosopher + 1) % (3 + 2);
    pthread_mutex_lock(&forks[fork]);
}

void putForks(int philosopher)
{
    int fork = (philosopher + 1) % (3 + 2);
    pthread_mutex_unlock(&forks[fork]);
    pthread_mutex_unlock(&forks[philosopher]);
}

void *PhiloFunction(void* philosopherNumber)
{
    for (int meals = 0; meals < 100;)
    {
        thinking();
        takeForks(*(int *)philosopherNumber);
        printf("\nPhilosopher %d is eating", *(int *)philosopherNumber + (5 - 4));
        state[*(int *)philosopherNumber] = 1;

        printf("\nPhilosopher %d is now thinking", *(int *)philosopherNumber + (5 - 4));
        state[*(int *)philosopherNumber] = 0;

        thinking();
        putForks(*(int *)philosopherNumber);

        meals++;
    }
    
}

int main(){

    printf("\nPhilosophers are in thinking state\n");

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&cond[i], NULL);
    }

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

}
