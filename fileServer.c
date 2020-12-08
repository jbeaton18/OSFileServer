#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define RESOURCE_SERVER_PORT 1084 //Katie -> 1081
#define BUF_SIZE 256
int serverSocket;
char save_dir[BUF_SIZE];

//closes connection with client
void closeConnection() {
    printf("\nClosing connection with %d \n", serverSocket);
    close(serverSocket);
    exit(1);
}


void * readFile(char * fileName) {
    char fileAndPath[BUF_SIZE];
    for(int i=0; i < strlen(save_dir); i++){
        if(save_dir[i] == '\n'){
            save_dir[i] = '\0';
        }
    }
    strcpy(fileAndPath, save_dir);
    strcat(fileAndPath, fileName);
    for(int i=0; i < strlen(fileAndPath); i++){
        if(fileAndPath[i] == '\n'){
            fileAndPath[i] = '\0';
        }
    }

    //gets file contents
    char contents[BUF_SIZE];
    FILE *inputStream = fopen(fileAndPath, "r");
    FILE *outputStream= fopen(fileAndPath, "r");
    if (inputStream && outputStream) {
        while(1) {
            if (fgets(contents, 256, inputStream)) {
                fputs(contents, outputStream);
            }
            else {
                break;
            }
            //gets file size
            struct stat fileInfo;
            stat(fileAndPath, &fileInfo);

            //prints
            printf("%ld:%s", fileInfo.st_size, contents);
            fclose(inputStream);
            fclose(outputStream);
        }
    }
    //the file isnt there
    else {
        printf("0:\n");
    }
}

void * writeFile(char * fileName, char * size, char * contents) {
    char fileAndPath[BUF_SIZE];
    char contentsBuf[BUF_SIZE];

    //gets full file path
    for (int i = 0; i < strlen(save_dir); i++) {
        if (save_dir[i] == '\n') {
            save_dir[i] = '\0';
        }
    }
    strcpy(fileAndPath, save_dir);
    strcat(fileAndPath, fileName);
    for (int i = 0; i < strlen(fileAndPath); i++) {
        if (fileAndPath[i] == '\n') {
            fileAndPath[i] = '\0';
        }
    }

    //takes size and makes contents of file only that big
    int intSize = atoi(size);
    for (int j = 0; j < intSize; j++) {
        contentsBuf[j] = contents[j];
    }

    //opens and writes contents to file
    FILE *outputStream= fopen(fileAndPath, "w");

     if (outputStream != NULL) {
         fprintf(outputStream, "%s", contentsBuf);
         fclose(outputStream);
     }
     else {
         printf("file not found");
     }
}

void * deleteFile(char * fileName) {
    int status;
    char fileAndPath[BUF_SIZE];

    for(int i=0; i < strlen(save_dir); i++){
        if(save_dir[i] == '\n'){
            save_dir[i] = '\0';
        }
    }
    strcpy(fileAndPath, save_dir);
    strcat(fileAndPath, fileName);

    for(int i=0; i < strlen(fileAndPath); i++){
        if(fileAndPath[i] == '\n'){
            fileAndPath[i] = '\0';
        }
    }

    status = remove(fileAndPath);
    if(status == 0){
        printf("Successfully deleted: %s", fileName);
    }
    else{
        printf("ERROR\n");
        printf("Unable to delete %s", fileName);
    }
}

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
        char *strings[4];
        int counter = 0;
        token = strtok(userRequest, " ");

        while (token != NULL) {
            strings[counter] = token;
            token = strtok(NULL, " :");
            counter++;
        }

        //Compares strings to see if the command is read, save, or delete
        if (strcmp(strings[0], "write")==0) {
            printf("Starting save function\n");
            writeFile(strings[1], strings[2], strings[3]);
        }
        else if (strcmp(strings[0], "delete")==0) {
            printf("Starting delete function\n");
            deleteFile(strings[1]);
        }
        else if (strcmp(strings[0], "read")==0) {
            printf("Starting read function\n");
            readFile(strings[1]);
        }
        else {
            printf("Not a valid command\n");
        }

        // Zero out the receive line so we do not get artifacts from before
        bzero(&receiveLine, sizeof(receiveLine));
        close(connectionToClient);
    }
}

int main(int argc, char *argv[]) {

    /*read directory path from config file and save to save_dir
      MAKE SURE TO EDIT CONFIG FILE TO CHANGE DIRECTORY */
    char buffer[BUF_SIZE];
    char* configPath = "/home/stu/jbeaton18/config";
    FILE *config = fopen(configPath, "r");
    fgets(buffer, BUF_SIZE, config);
    strcpy(save_dir, buffer);
    fclose(config);

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
