#include "MySerialServer.h"

#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>

#include <strings.h>
#include <cstring>
#include <sstream>

struct thread_params {
    server_side::ClientHandler *ch;
    int sockfd;
};

void *thread_func(void *arg) {
    char buf[1024]; // max message in size of 1024
    ssize_t msglen = 0; // message length received from client.

    int clientfd;
    socklen_t addr_len;
    struct sockaddr_in cli_addr;
    struct thread_params *params = (struct thread_params *) arg;
    // listen to up to 5 clients
    listen(params->sockfd, 5);

    bool isAcceptingNewClients = true;
    while (isAcceptingNewClients) {
        fd_set set;
        struct timeval timeout;
        int rv;

        FD_ZERO(&set); /* clear the set */
        FD_SET(params->sockfd, &set); /* add our file descriptor to the set */
        timeout.tv_sec = 60; // 10 secs timeout
        timeout.tv_usec = 0; // this is 0 because all the internet examples showed that.


        printf("[Server]: Waiting for %d seconds for the next client\n", (int)timeout.tv_sec);
        rv = select(params->sockfd + 1, &set, NULL, NULL, &timeout);
        if(rv == -1){
            perror("select");
            // TODO : decide what to do - because this is system call error.
            // right now - stop the server
            isAcceptingNewClients = false;
            break;
        }else if(rv == 0){
            // timeout with a single client - close all connections
            printf("timeout occurred.. stopping server \n"); /* a timeout occured */
            isAcceptingNewClients = false;
            break;
        }
        // else - accept connection

        addr_len = sizeof(struct sockaddr_in);
        clientfd = accept(params->sockfd, (struct sockaddr *) &cli_addr, &addr_len);
        if (clientfd < 0) {
            // if accept failed stop accepting clients. (may be changed - but its simplest currently)
            perror("accept failed");
            isAcceptingNewClients = false;
            break;
        }
        printf("[Server]: Client with fd %d connected\n", clientfd);
        // now we got clientfd.
        // we can read from the client.


        bool isHandlingClient = true;
        while (isHandlingClient) {
            //Receive a message from client, and handle it
            memset(buf, 0, sizeof(buf));
            msglen = read(clientfd, buf, sizeof(buf));
            if (msglen <= 0) {
                perror("error reading from client");
                isHandlingClient = false;
                break;
            }

            // if the message is "end" - end the conversation.
            if (strcmp("end", buf) == 0 || strcmp("end\n", buf) == 0) {
                // end - dont read or handle any more messages from the client.
                isHandlingClient = false;
                break;
            }

            // ClientHandler has a function called handleClient,
            // reciving string as input and stream for output.
            std::string in(buf);
            // now we need to create outputstream, to which the client handler will write into.
            std::ostringstream os;
            // now - use the clienthandler to handle the request
            params->ch->handleClient(in, os);

            // now write back to the client the message.
            std::string tmp = os.str();
            size_t client_msg_len = tmp.length();
            const char* msg_to_client = tmp.c_str();
            if(write(clientfd, msg_to_client,client_msg_len) < client_msg_len){
                perror("error while writing to client");
                isHandlingClient = false;
                break;
            }
        }
        printf("[Server]: Closing connection with client with fd %d\n", clientfd);
        // close connection with client. returns != 0 if error
        if(close(clientfd)){
            perror("Error while closing client connection.");
            // TODO : decide what to do in this case. now doing nothing and continuing to next client
        }
    } // accepting new clients code.

    delete params;
}


/*
 * this func open thread .
 */
void server_side::MySerialServer::open(int port, server_side::ClientHandler *ch) {
    // setup the socket
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw "ERROR opening socket";
    }
    bzero((char *) &serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw "ERROR on binding";
    }

    // leave the listen and accept things to the thread.
    // therefore we need the sockfd in the thread. save it in the args.

    struct thread_params *args = new thread_params();
    // init the thread arguments (thread params)
    args->ch = ch;
    args->sockfd = sockfd;
    // done initializing the thread arguments - create and start the thread.

    if (pthread_create(&tid, NULL, thread_func, args)) {
        throw "Error creating server thread";
    }
}

void server_side::MySerialServer::stop() {
    // first - close the thread.
    printf("[server]: waiting for thread to stop...\n");
    if(pthread_join(tid, NULL)){
        throw "Error waiting to client handling thread to finish";
    }
    printf("[server]: client thread stopped...\n");

    // then - close the socket.
    if(shutdown(sockfd, 2)){
        throw "Failed to close the server socket";
    }
}