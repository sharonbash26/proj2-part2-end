//
// Created by sharon_i4 on 07/01/2019.
//

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFSIZE];

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    /* Create a net point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening net");
        exit(1);
    }

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    int numOfInputsAfterEnd = 0;

    /* Now ask for a message from the user, this message
       * will be read by server
    */
    while(numOfInputsAfterEnd <= 2) {
        printf("Please enter the message: ");
        bzero(buffer, BUFSIZE);
        fgets(buffer, BUFSIZE-1, stdin);

        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));
        printf("wrote the message!\n");
        if (n < 0) {
            perror("ERROR writing to net");
            exit(1);
        }

        if(numOfInputsAfterEnd){
            ++numOfInputsAfterEnd;
        }
        if(!strcmp("end", buffer) || !strcmp("end\n", buffer)){
            numOfInputsAfterEnd++;
        }
        printf("%s\n", buffer);
    }

    /* Now read server response */
    bzero(buffer, BUFSIZE);
    n = read(sockfd, buffer, BUFSIZE-1);

    if (n < 0) {
        perror("ERROR reading from net");
        exit(1);
    }

    printf("'%s'\n", buffer);

    close(sockfd);
    return 0;
}