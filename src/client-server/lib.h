//
// Created by Rocco Del Prete on 16/10/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#ifndef CLIENT_SERVER_LIB_H
#define CLIENT_SERVER_LIB_H

/**
 * @param IPFamily – IP addresses family
 * @param type – stream type
 * @param protocol – protocol to use
 * @return the descriptor created or exit if socket
 * method go in error
 */
int openSocket(int IPFamily, int type, int protocol);


void portToNetwork(int IPFamily, char **argv, struct in_addr sin_addr);


void connectToSocket(int socketDescriptor, struct sockaddr *socketInfos, int size);


void assignAddress(int socketDescriptor, struct sockaddr *socketInfos, int size);


void socketInListenMode(int socketDescriptor, int length);


int acceptConnection(int socketDescriptor, struct sockaddr *client, socklen_t *addressSize);

ssize_t fullWrite(int fileDescriptor, const void *buffer, size_t count);

ssize_t fullRead(int fileDescriptor, void *buffer, size_t count);

#endif //CLIENT_SERVER_LIB_H
