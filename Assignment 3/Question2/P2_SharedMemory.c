# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <time.h>

# define SHM_SIZE 12

void printBuffer(char buffer[SHM_SIZE])
{
    printf("Received: ");
    for (int i = 0; i <= SHM_SIZE - 3; i++) {
        printf("%c", buffer[i]);
    }

    printf(" with ID: %d", (int) buffer[SHM_SIZE - 2]);

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

    data = shmat(shmid, NULL, 0);
    while (data[0] != 16)
    {
        int i = 0;
        while (i < 5)
        {
            int j = 0;
            while (j < 20)
            {
                characters[count][j] = data[j];
                j++;
            }
            count++;
            i++;

            printBuffer(data);
        }
    }
    int max = 0;
    for (int i = 0; i < 50; i++)
    {
        if (characters[i][20] > max)
        {
            max = characters[i][20];
        }

    }
    
    data[0] = 16;
    exit(EXIT_SUCCESS);
}