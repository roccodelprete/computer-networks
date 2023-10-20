//
// Created by Rocco Del Prete on 16/10/23.
//

#include "lib.h"

int openSocket(int IPFamily, int type, int protocol) {
    int socketDescriptor;

    if ((socketDescriptor = socket(IPFamily, type, protocol)) < 0) {
        perror("Error in socket opening...\n");
        exit(1);
    }

    return socketDescriptor;
}

void portToNetwork(int IPFamily, char **argv, struct in_addr sin_addr) {
    if ((inet_pton(IPFamily, argv[1], &sin_addr)) <= 0) {
        perror("Error in pton function...\n");
        exit(1);
    }
}

void connectToSocket(int socketDescriptor, struct sockaddr *socketInfos, int size) {
    if ((connect(socketDescriptor, socketInfos, size)) < 0) {
        perror("Error to connect to socket...\n");
        exit(1);
    }
}

void assignAddress(int socketDescriptor, struct sockaddr *socketInfos, int size) {
    if ((bind(socketDescriptor, socketInfos, size)) < 0) {
        perror("Error assigning address...\n");
        exit(1);
    }
}

void socketInListenMode(int socketDescriptor, int length) {
    if ((listen(socketDescriptor, length)) < 0) {
        perror("Error in socket listening...\n");
        exit(1);
    }
}

int acceptConnection(int socketDescriptor, struct sockaddr *client, socklen_t *addressSize) {
    int connectionDescriptor;

    if ((connectionDescriptor = accept(socketDescriptor, client, addressSize)) < 0) {
        perror("Error accepting connection...\n");
        exit(1);
    }

    return connectionDescriptor;
}

ssize_t fullWrite(int fileDescriptor, const void *buffer, size_t count) {
    size_t charactersLeft;
    ssize_t charactersWritten;
    charactersLeft = count;

    while (charactersLeft > 0) {
        if ((charactersWritten = write(fileDescriptor, buffer, charactersLeft)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                perror("system call EINTR");
                exit(1);
            }
        }
        charactersLeft -= charactersWritten;
        buffer += charactersWritten;
    }
    return (charactersLeft);
}

ssize_t fullRead(int fileDescriptor, void *buffer, size_t count) {
    size_t charactersLeft;
    ssize_t charactersRead;
    charactersLeft = count;

    while (charactersLeft > 0) {
        if ((charactersRead = read(fileDescriptor, buffer, count)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                perror("system call EINTR");
                exit(1);
            }
        } else if (charactersRead == 0) /* EOF */ {
            break;
        }
        charactersLeft -= charactersRead;
        buffer += charactersRead;
    }
    buffer = 0;
    return (charactersLeft);
}

