# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define BUFFER_SIZE 12

void makeFIFO(char *name)
{
    mkfifo(name, 0666);
}

int openFIFO(char *name, int flag)
{
    int fd = 0;
    fd = open(name, flag);
    return fd;
}

int changeToInteger(char *buffer, int decr)
{
    int integer = 0;
    integer = (int) buffer[BUFFER_SIZE-decr];
    return integer;
}

void printBuffer(char *buffer, int count)
{
    int decr = 2;
    int end = BUFFER_SIZE- (2 + 1);
    int countcheck = count % (3 + 2);

    printf("Received string: ");
    for (int i = 0; i <= end; i++){
        printf("%c",buffer[i]);
    }

    printf(" with ID: %d\n", changeToInteger(buffer, decr));
    if (countcheck == 0)
    {
        printf("\n");
    }
}

void closeFIFO(int fd)
{
    int closing = 0;
    closing = close(fd);
}

int main(int argc, char *argv[])
{
    int fd1 = 0;
    int fd2 = 0;
    int update = 0;
    char buffer[BUFFER_SIZE];
    char fifo1 [] = "myFIFO";
    char fifo2 [] = "myFIFO2";
    int count = 1;

    makeFIFO(fifo1);
    makeFIFO(fifo2);
    
    for (; count <= 50; count++)
    {
        int countcheck = count % (3 + 2);

        fd1 = open(fifo1, 00);

        update = read(fd1, buffer, sizeof(buffer));

        printBuffer(buffer, count);

        closeFIFO(fd1);

        if (countcheck == 0)
        {
            fd2 = open(fifo2, 01);

            update = write(fd2, buffer, strlen(buffer)+1);

            closeFIFO(fd2);
        }
    }

    return 0;
}