#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

//i dont think we need this when we run on the server, but clion was giving me issues
#include <winsock2.h>

#define RESOURCE_SERVER_PORT 108
#define BUF_SIZE 256
int serverSocket;

//closes connection with client
void closeConnection() {
    printf("\nClosing connection with %d \n", serverSocket);
    close(serverSocket);
    exit(1);
}


//TODO  read filename -> return size and contents of file

//TODO write filename n:[contents] -> saves files in cache with n being size

//TODO delete filename -> deletes file from cache



//processes what was sent from the client, called by the popup thread
void * processClientRequest(void * request) {
    int connectionToClient = *(int *)request;
    char receiveLine[BUF_SIZE];
    char sendLine[BUF_SIZE];

    int bytesReadFromClient = 0;
    while ( (bytesReadFromClient = read(connectionToClient, receiveLine, BUF_SIZE)) > 0);
        receiveLine[bytesReadFromClient] = 0;

        // prints to buffer
        snprintf(sendLine, sizeof(sendLine), "true");

        /* Writes to client
        printf("Sending s\n", sendLine);
        write(connectionToClient, sendLine, strlen(sendLine));
         */

        //clears receiveLine
        bzero(&receiveLine, sizeof(receiveLine));
        close(connectionToClient);
    }

int main(int argc, char *argv[]) {
    int connectionToClient, bytesReadFromClient;

    // Create a server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family      = AF_INET;

    // INADDR_ANY -> listen to any address
    // htonl and htons -> converts address/ports to network formats
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port        = htons(RESOURCE_SERVER_PORT);

    //binds to port
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        printf("Unable to bind to port\n");
        exit(-1);
    }

    // register for Ctrl+C being sent to close connection
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = closeConnection;
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
    listen(serverSocket);

    while (1) {
        connectionToClient = accept(serverSocket, (struct sockaddr *) NULL, NULL);
        pthread_t someThread;
        pthread_create(&someThread, NULL, processClientRequest, (void *)&connectionToClient);

    }
}
