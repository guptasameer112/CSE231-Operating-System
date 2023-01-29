# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <unistd.h>
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

int createSocket(int data_socket)
{
    data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    return data_socket;
}

int connectToP2(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int connecting;
    connecting = connect(sockfd, addr, addrlen);
    return connecting;
}

int readFromSocket(int sockfd, void *buf, size_t len, int count)
{
    int reading;
    reading = read(sockfd, buf, len);
    return reading;
}

int writeToSocket(int sockfd, const void *buf, size_t len)
{
    int writing;
    writing = write(sockfd, buf, len);
    return writing;
}

int closeSocket(int sockfd)
{
    int closing;
    closing = close(sockfd);
    return closing;
}

int main(int argc, char* argv[])
{
    struct sockaddr_un socket_addr;
    int data_socket;
    int val;
    int count = 0;
    char buffer[BUFFER_SIZE];
    char characters[50][BUFFER_SIZE] = {{0}};

    clock_t start, end;

    generateRandomStrings(characters);

    data_socket = createSocket(data_socket);

    memset(&socket_addr, 0, sizeof(socket_addr));
    socket_addr.sun_family = AF_UNIX;
    strncpy(socket_addr.sun_path, "mySocket.socket", sizeof(socket_addr.sun_path) - 1);

    int size = sizeof(socket_addr.sun_family) + strlen(socket_addr.sun_path);
    val = connectToP2(data_socket, (const struct sockaddr *) &socket_addr, size);    

    start = clock();
    while(count < 50)
    {
        int length = strlen(characters[count]) + 5;
        for (int i = 0; i < 5; i++)
        {
            val = writeToSocket(data_socket, characters[count], length - 4);
            count++;
        }

        strcpy(buffer, "BREAK");

        int bufferLength = strlen(buffer) + 5;
        val = writeToSocket(data_socket, buffer, bufferLength - 4);
        memset(buffer, 0, sizeof(buffer));
        
        val = readFromSocket(data_socket, buffer, BUFFER_SIZE, count);

        printf("Highest ID: %d\n", (int) buffer[BUFFER_SIZE - 2]);
        memset(buffer, 0, sizeof(buffer));
    }
    end = clock();

    double time_taken = ((double) (end - start)) / 1000000;
    printf("Time taken: %f\n", time_taken);

    val = closeSocket(data_socket);

    exit(EXIT_SUCCESS);
}
