# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <time.h>

# define BUFFER_SIZE 12

char generateRandomStrings(char characters[50][BUFFER_SIZE])
{
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 10; j++){
            characters[i][j] = (rand() % 26) + 97;
        }
        characters[i][10] = i+1;
    }
    
    return characters[50][BUFFER_SIZE];
}

void openFIFO(char *name)
{
    mkfifo(name, 0666);
}

int openFD(char *myFIFO, int flag)
{
    int fd = 0;
    fd = open(myFIFO, flag);
    return fd;
}

int writeFD(int i, int fd, char characters[50][BUFFER_SIZE], int count)
{
    int writing = 0;
    int counter = count * (3 + 2) + i;
    int length = strlen(characters[count]) + 5;
    writing = write(fd, characters[counter], length - 4);
    return writing;
}

int readFD(int fd, char *buffer)
{
    int reading = 0;
    reading = read(fd, buffer, BUFFER_SIZE);
    return reading;
}

int closeFD(int fd)
{
    int closing = 0;
    closing = close(fd);
    return closing;
}

int main(int argc, char *argv[])
{
    int fd = 0;
    int fd2 = 0;
    int val = 0;
    int count = 0;
    char buffer[BUFFER_SIZE];
    char myFIFO [] = "myFIFO";
    char myFIFO2 [] = "myFIFO2";
    char characters[50][BUFFER_SIZE] = {{0}};
    int decr = 2;

    clock_t start, end;

    openFIFO(myFIFO);
    openFIFO(myFIFO2);
    generateRandomStrings(characters);
    
    start = clock();

    for (; count < 10; count++)
    {
        fd = openFD(myFIFO, 01);

        int i = 0;
        while (i < 5)
        {
            val = writeFD(i, fd, characters, count);
            i++;
        }

        val = closeFD(fd);
        
        fd2 = openFD(myFIFO2, 00);

        val = readFD(fd2, buffer);

        int end = BUFFER_SIZE - (1 + 1);

        int max = (int) buffer[end];

        printf("Highest ID received is %d\n", max);

        val = close(fd2);

    }
    end = clock();

    double time_taken = ((double) (end - start)) / 1000000;
    printf("Time taken to execute: %f seconds\n", time_taken);

    unlink(myFIFO);
    unlink(myFIFO2);
    return 0;
}