//
// Created by Rocco Del Prete on 23/10/23.
//

#include "lib.h"

int main(int argc, char **argv) {
    int socketDescriptor, numBytesRead;
    char receiptLine[1025];
    struct sockaddr_in client;
    struct hostent *host = gethostbyname(argv[1]);

    if (argc != 2) {
        fprintf(stderr, "usage: %s <IP ADDRESS>\n", argv[0]);
        exit(1);
    }

    socketDescriptor = openSocket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(1024);

    /**
     * This is the way without passing the hostname by argument
    */
    // portToNetwork(AF_INET, argv, client.sin_addr);
    portToNetworkWithHostname(AF_INET, host->h_addr_list, client.sin_addr);
    connectToSocket(socketDescriptor, (struct sockaddr *) &client, sizeof(client));

    numBytesRead = fullRead(socketDescriptor, receiptLine, sizeof(receiptLine));

    if (numBytesRead < 0) {
        exit(1);
    }

    if (fputs(receiptLine, stdout) == EOF) {
        perror("fputs error...\n");
        exit(1);
    }

    return 0;
}
