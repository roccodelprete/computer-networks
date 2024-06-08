//
// Created by Rocco Del Prete on 23/10/23.
//

#ifndef lib_h
#define lib_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>

/**
 * function to create a socket
 * @param IPFamily IP addresses family
 * @param type stream type
 * @param protocol protocol to use
 * @return the descriptor created or exit if socket
 * method go in error
 */
int openSocket(int IPFamily, int type, int protocol);

/**
 * function to associate port to network
 * using inet_pton
 * @param IPFamily IP addresses family
 * @param argv buffer arguments passed from terminal
 * @param sin_addr IP address
 */
void portToNetwork(int IPFamily, char **argv, struct in_addr sin_addr);

/**
 * function to associate port to network
 * using inet_pton with given host name
 * @param IPFamily IP addresses family
 * @param argv buffer arguments passed from terminal
 * @param sin_addr IP address
 */
void portToNetworkWithHostname(int IPFamily, char **host, struct in_addr sin_addr);

/**
 * function to associate port to network
 * using inet_ntop
 * @param IPFamily IP addresses family
 * @param argv buffer arguments passed from terminal
 * @param sin_addr IP address
 */
void portToNetworkNtop(int IPFamily, struct in_addr *sin_addr, char *buffer, socklen_t length);

/**
 * function to connect socket to IP address
 * @param socketDescriptor the socket
 * @param socketInfos the socket infos (included IP address)
 * @param size socket infos struct size
 */
void connectToSocket(int socketDescriptor, struct sockaddr *socketInfos, int size);

/**
 * function to assign address to socket
 * @param socketDescriptor the socket
 * @param socketInfos the socket infos
 * @param size socket infos struct size
 */
void assignAddress(int socketDescriptor, struct sockaddr *socketInfos, int size);

/**
 * function to put a socket in listen
 * @param socketDescriptor the socket
 * @param length maximum connection that will be accepted
 */
void socketInListenMode(int socketDescriptor, int length);

/**
 * function to accept a connection
 * @param socketDescriptor the socket
 * @param client client who want the connection
 * @param addressSize client address size
 * @return the connection accepted
 */
int acceptConnection(int socketDescriptor, struct sockaddr *client, socklen_t *addressSize);

/**
 * function to write on a socket
 * @param fileDescriptor where to write
 * @param buffer what to write
 * @param count how many bytes to write
 * @return the number bytes written
 */
ssize_t fullWrite(int fileDescriptor, const void *buffer, size_t count);

/**
 * function to read from a socket
 * @param fileDescriptor where to read
 * @param buffer what to read
 * @param count how many bytes to read
 * @return the number bytes read
 */
ssize_t fullRead(int fileDescriptor, void *buffer, size_t count);

#endif
