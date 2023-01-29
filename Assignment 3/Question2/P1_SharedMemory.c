# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <time.h>

# define SHM_SIZE 12

void generateRandomString(char characters[50][SHM_SIZE])
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            characters[i][j] = 'a' + (rand() % 26);
        }
        characters[i][10] = i + 1;
    }
}


int main(int argc, char *argv[])
{
    key_t key = ftok("shmfile", 1);
    char *data;
    int count = 0;
    char characters[50][SHM_SIZE];
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    generateRandomString(characters);
    clock_t start, end;

    data = shmat(shmid, NULL, 0);
    start = clock();

    while (count < 50)
    {
        int i = 0;
        while (i < 5)
        {
            int j = 0;
            while (j < 20)
            {
                data[j] = characters[count][j];
                j++;
            }
            data[20] = count;
            data[21] = 1;
            while (data[21] != 2)
            {
            }
            count++;
            i++;
        }

        int max = 0;
        int maxIndex = 0;
        for (int i = 0; i < 5; i++)
        {
            if (data[i] > max)
            {
                max = data[i];
                maxIndex = i;
            }
        }

        printf("Max: %d", maxIndex + 1);
    }

    shmctl(shmid, IPC_RMID, NULL);

    end = clock();
    double time_taken = ((double)(end - start)) / 1000000;
    printf("Time taken: %f\n", time_taken);

    exit(EXIT_SUCCESS);
}

