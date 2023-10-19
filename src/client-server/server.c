#include "lib.h"

int main() {
    int socketDescriptor, connectionDescriptor;
    struct sockaddr_in server;
    char buffer[4096];
    time_t ticks = time(NULL);

    socketDescriptor = openSocket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1025);

    assignAddress(socketDescriptor, (struct sockaddr *) &server, sizeof(server));
    socketInListenMode(socketDescriptor, 1024);

    while (1) {
        connectionDescriptor = acceptConnection(socketDescriptor, (struct sockaddr *) NULL, NULL);
        snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
        if ((write(connectionDescriptor, buffer, strlen(buffer))) != strlen(buffer)) {
            perror("Error writing...\n");
            exit(1);
        }
        close(connectionDescriptor);
    }
}
