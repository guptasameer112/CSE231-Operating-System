# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include <unistd.h>

int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param);
int nice(int increment);

void *countA(void *arg);
void *countB(void *arg);
void *countC(void *arg);

float timeA;
float timeB;
float timeC;

int policy1 = SCHED_OTHER;
int policy2 = SCHED_RR;
int policy3 = SCHED_FIFO;

struct sched_param param;

void *countA(void *arg)
{
    int nice_value = 0;
    int ret = nice(nice_value);
    if (ret == -1)
    {
        printf("Error in setting nice value");
    }

    else
    {
        printf("%d \n", ret);

        struct timespec start, end;
        
        clock_gettime(CLOCK_REALTIME, &start);

        long long int i;
        for (i = 1; i <= pow(2, 32); i++);
        
        clock_gettime(CLOCK_REALTIME, &end);
        
        timeA = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    }

    return NULL;
}

void *countB(void *arg)
{
    pthread_setschedparam(pthread_self(), policy2, &param);
    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);
    
    long long int i;
    for (i = 1; i <= pow(2, 32); i++);

    clock_gettime(CLOCK_REALTIME, &end);
    
    timeB = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    return NULL;
}

void *countC(void *arg)
{
    pthread_setschedparam(pthread_self(), policy3, &param);
    struct timespec start, end;
    
    clock_gettime(CLOCK_REALTIME, &start);

    long long int i;
    for (i = 1; i <= pow(2, 32); i++);

    clock_gettime(CLOCK_REALTIME, &end);

    timeC = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    return NULL;
}

int main()
{
    pthread_t pthread_id[3];
    
    int ThrA, ThrB, ThrC;

    ThrA = pthread_create(&pthread_id[0], NULL, countA, &param);
    
    if (ThrA != 0) 
    {
        perror("pthread_create");
        exit(1);
    }
    

    if (ThrA != 0) 
    
    {
        perror("pthread_join");
        exit(1);
    }

    param.sched_priority = 50;

    ThrB = pthread_create(&pthread_id[1], NULL, countB, &param);

    if (ThrB != 0) 
    {
        perror("pthread_create");
        exit(1);
    }


    if (ThrB != 0) 
    
    {
        perror("pthread_join");
        exit(1);
    }

    param.sched_priority = 50;

    ThrC = pthread_create(&pthread_id[2], NULL, countC, NULL);

    if (ThrC != 0) 
    {
        perror("pthread_create");
        exit(1);
    }


    if (ThrC != 0) 
    
    {
        perror("pthread_join");
        exit(1);
    }

    ThrA = pthread_join(pthread_id[0], NULL);
    ThrB = pthread_join(pthread_id[1], NULL);
    ThrC = pthread_join(pthread_id[2], NULL);

    printf("timeA = %f", timeA);
    printf("\n");
    printf("timeB = %f", timeB);
    printf("\n");
    printf("timeC = %f", timeC);
    printf("\n");

    return 0;
}

