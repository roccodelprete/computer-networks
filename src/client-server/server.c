#include "lib.h"

int clientsNumber = 0;

void handler() {
    clientsNumber++;
    printf("Client number %d\n", clientsNumber);
}

int main() {
    signal(SIGCHLD, (void (*)(int))handler);

    int socketDescriptor, connectionDescriptor, charactersWritten;
    struct sockaddr_in server, client;
    socklen_t length;
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    time_t timeVal = time(NULL);
    int logging = 1;
    pid_t pid;

    /**
     * fullWrite code section
     */
//    socketDescriptor = openSocket(AF_INET, SOCK_STREAM, 0);
//
//    server.sin_family = AF_INET;
//    server.sin_addr.s_addr = htonl(INADDR_ANY);
//    server.sin_port = htons(1025);
//
//    assignAddress(socketDescriptor, (struct sockaddr *) &server, sizeof(server));
//    socketInListenMode(socketDescriptor, 1024);
//
//    while (1) {
//        connectionDescriptor = acceptConnection(socketDescriptor, (struct sockaddr *) NULL, NULL);
//        *//* Disable this line to test fullRead and fullWrite *//*
//        // snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
//
//        charactersWritten = fullWrite(connectionDescriptor, buffer, sizeof(buffer));
//
//        if (charactersWritten <= 0) {
//            exit(1);
//        }
//
//        close(connectionDescriptor);
//    }

    /**
     * Concurrent server code section
     */
    socketDescriptor = openSocket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1024);

    assignAddress(socketDescriptor, (struct sockaddr *) &server, sizeof(server));
    socketInListenMode(socketDescriptor, 20);

    while (1) {
        length = sizeof(client);
        connectionDescriptor = acceptConnection(socketDescriptor, (struct sockaddr *) NULL, NULL);

        if ((pid = fork()) < 0) {
            perror("fork");
            exit(-1);
        }

        if (pid == 0) {
            close(socketDescriptor);
            snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&timeVal));
            charactersWritten = fullWrite(connectionDescriptor, buffer, sizeof(buffer));

            if (logging) {
                portToNetworkNtop(AF_INET, &(client.sin_addr), buffer, sizeof(buffer));
                printf("\nRequest from host %s, port %d\n", buffer, ntohs(client.sin_port));
            }

            close(connectionDescriptor);
            exit(0);
        } else {
            close(connectionDescriptor);
        }
    }
}