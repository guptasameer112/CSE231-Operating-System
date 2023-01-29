# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <sys/signal.h>
# include <unistd.h>

# define SOCKET_NAME "mySocket.socket"
# define BUFFER_SIZE 12

int connectToSocket(int connection_socket)
{
    connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    return connection_socket;
}

int bindToSocket(int binding, int connection_socket, struct sockaddr_un socket_addr)
{
    binding = bind(connection_socket, (const struct sockaddr *) &socket_addr, sizeof(socket_addr));
    return binding;
}

int listenToSocket(int listening, int connection_socket)
{
    listening = listen(connection_socket, 2);
    return listening;
}

int acceptConnection(int data_socket, int connection_socket)
{
    data_socket = accept(connection_socket, NULL, NULL);
    return data_socket;
}

int readFromSocket(int ret)
{
    if (ret == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

int writeToSocket(int ret)
{   
    if (ret == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

int closeDataSocket(int data_socket)
{
    close(data_socket);

    return data_socket;
}

int closeConnectionSocket(int connection_socket)
{
    close(connection_socket);
    return connection_socket;
}

int unlinkSocket()
{
    unlink(SOCKET_NAME);
    return 0;
}

void printBuffer(char buffer[BUFFER_SIZE])
{
    printf("Received: ");
    int end = BUFFER_SIZE - 2;
    for (int i = 0; i <= end - 1; i++) 
    {
        printf("%c", buffer[i]);
    }

    printf(" with ID: %d", (int) buffer[BUFFER_SIZE - 2]);

}

int main(int argc, char *argv[])
{
    struct sockaddr_un socket_addr;
    int val;
    int connection_socket;
    int data_socket;
    int down = 0;
    char buffer[BUFFER_SIZE];

    connection_socket = connectToSocket(connection_socket);

    memset(&socket_addr, 0, sizeof(socket_addr));
    socket_addr.sun_family = AF_UNIX;
    strncpy(socket_addr.sun_path, SOCKET_NAME, sizeof(socket_addr.sun_path) - 1);

    val = bindToSocket(val, connection_socket, socket_addr);

    val = listenToSocket(val, connection_socket);

    data_socket = acceptConnection(data_socket, connection_socket);

    int count = 0;

    while(!down) {
        for (int i = 0; i < 5; i++) {

            count++;
            val = read(data_socket, buffer, sizeof(buffer));

            int checkLast = !strncmp(buffer, "BREAK", sizeof(buffer));
            int size = sizeof(buffer) + 5;
            buffer[size - 4] = 0;
            int end  = (int) buffer[BUFFER_SIZE - 2] + (3 + 2); 
            
            if (checkLast) 
            {
                count--;
                if(count >= 50){
                    down = 1;
                }
                break;
            }

            if ((end - (3 + 2)) % 5 == 0){
                val = write(data_socket, buffer, sizeof(buffer));
                writeToSocket(val);
            }

            printBuffer(buffer);
            printf("\n");

        }
        
        printf("\n");
    }

    data_socket = closeDataSocket(data_socket);

    connection_socket = closeConnectionSocket(connection_socket);

    unlinkSocket();

    exit(EXIT_SUCCESS);
}