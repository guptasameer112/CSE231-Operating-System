#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param);

float timeA;
float timeB;
float timeC;

struct sched_param param;

int main()
{
    struct timespec start, end;
     
    pid_t pid1;
    
    clock_gettime(CLOCK_REALTIME, &start);

    pid1 = fork();
    if (pid1 == 0)
    {
        param.sched_priority = 0;
        int a = sched_setscheduler(0, SCHED_OTHER, &param);
        if (execl("script.sh", (char*)NULL) == -1)
        {
            perror("compilation error in fork1");
        }
    }   
    else if (pid1 < 0)
    {
        perror("fork1 error");
    }
    else
    {
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        timeA = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

        pid_t pid2;
        clock_gettime(CLOCK_REALTIME, &start);
        pid2 = fork();
        if (pid2 == 0)
        {
            param.sched_priority = 50;
            int b = sched_setscheduler(0, SCHED_FIFO, &param);
            if (execl("script.sh", (char*)NULL) == -1)
            {
                perror("compilation error in fork2");
            }
        }

        else if (pid2 < 0)
        {
            perror("fork2 error");
        }

        else
        {
            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &end);
            timeB = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

            pid_t pid3;
            pid3 = fork();
            if (pid3 == 0)
            {
                param.sched_priority = 50;
                int c = sched_setscheduler(0, SCHED_RR, &param);
                if (execl("script.sh", (char*)NULL) == -1)
                {
                    perror("compilation error in fork3");
                }
            }
            else if (pid3 < 0)
            {
                perror("fork3 error");
            }
            else
            {
                wait(NULL);
                clock_gettime(CLOCK_REALTIME, &end);
                timeC = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            }
        }
    }
    return 0;
}

