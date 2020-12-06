#include <sys/socket.h> //works on server
#include <netinet/in.h>  //works on server
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>


#define RESOURCE_SERVER_PORT 1084
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
    // Read the request that the client has
    while ( (bytesReadFromClient = read(connectionToClient, receiveLine, BUF_SIZE)) > 0) {
        //add null terminator
        receiveLine[bytesReadFromClient] = 0;
        //copy receive line to new string
        char userRequest[strlen(receiveLine)];
        strcpy(userRequest, receiveLine);

        /* Breaks into multiple strings and store into array strings[]
           First element will be command, second will be file name, if there
           is a third it is the size:[contents] */
        char * token;
        char *strings[3];
        int counter = 0;
        token = strtok(userRequest, " ");

        while (token != NULL) {
            strings[counter] = token;
            token = strtok(NULL, " ");
            counter++;
        }

        //Compares strings to see if the command is read, save, or delete
        if (strcmp(strings[0], "save")==0) {
            printf("True!");
        }
        else if (strcmp(strings[0], "delete")==0) {
            printf("True!");
        }
        else if (strcmp(strings[0], "read")==0) {
            printf("True!");
        }
        else {
            printf("False!");

        }


        // Zero out the receive line so we do not get artifacts from before
        bzero(&receiveLine, sizeof(receiveLine));
        close(connectionToClient);
    }
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

    //register for Ctrl+C being sent to close connection
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = closeConnection;
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
    listen(serverSocket, 10);

    while (1) {
        connectionToClient = accept(serverSocket, (struct sockaddr *) NULL, NULL);

        //threads for requests
        pthread_t someThread;
        pthread_create(&someThread, NULL, processClientRequest, (void *)&connectionToClient);

    }
}
