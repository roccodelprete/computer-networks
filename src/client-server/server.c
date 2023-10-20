#include "lib.h"

int main() {
    int socketDescriptor, connectionDescriptor, charactersWritten;
    struct sockaddr_in server;
    char buffer[100] = {'p', 'r', 'o', 'v', 'a'};
    time_t ticks = time(NULL);

    socketDescriptor = openSocket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1025);

    assignAddress(socketDescriptor, (struct sockaddr *) &server, sizeof(server));
    socketInListenMode(socketDescriptor, 1024);

    while (1) {
        connectionDescriptor = acceptConnection(socketDescriptor, (struct sockaddr *) NULL, NULL);
        /* Disable this line to test fullRead and fullWrite */
        // snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));

        charactersWritten = fullWrite(connectionDescriptor, buffer, sizeof(buffer));

        if (charactersWritten <= 0) {
            exit(1);
        }

        close(connectionDescriptor);
    }
}
