//
// Created by Rocco Del Prete on 23/10/23.
//

#include "lib.h"

int openSocket(int IPFamily, int type, int protocol) {
    int socketDescriptor;

    if ((socketDescriptor = socket(IPFamily, type, protocol)) < 0) {
        perror("socket\n");
        exit(1);
    }

    return socketDescriptor;
}

void portToNetworkWithHostname(int IPFamily, char **host, struct in_addr sin_addr) {
    if ((inet_pton(IPFamily, host[0], &sin_addr)) < 0) {
        perror("pton");
        exit(1);
    }
}

void portToNetwork(int IPFamily, char **argv, struct in_addr sin_addr) {
    if ((inet_pton(IPFamily, argv[1], &sin_addr)) <= 0) {
        perror("pton");
        exit(1);
    }
}

void portToNetworkNtop(int IPFamily, struct in_addr *sin_addr, char *buffer, socklen_t length) {
    if ((inet_ntop(IPFamily, sin_addr, buffer, length)) == NULL) {
        perror("ntop");
        exit(1);
    }
}

void connectToSocket(int socketDescriptor, struct sockaddr *socketInfos, int size) {
    if ((connect(socketDescriptor, socketInfos, size)) < 0) {
        perror("connect");
        exit(1);
    }
}

void assignAddress(int socketDescriptor, struct sockaddr *socketInfos, int size) {
    if ((bind(socketDescriptor, socketInfos, size)) < 0) {
        perror("bind");
        exit(1);
    }
}

void socketInListenMode(int socketDescriptor, int length) {
    if ((listen(socketDescriptor, length)) < 0) {
        perror("listen");
        exit(1);
    }
}

int acceptConnection(int socketDescriptor, struct sockaddr *client, socklen_t *addressSize) {
    int connectionDescriptor;

    if ((connectionDescriptor = accept(socketDescriptor, client, addressSize)) < 0) {
        perror("accept");
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
        if ((charactersRead = read(fileDescriptor, buffer, charactersLeft)) < 0) {
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
