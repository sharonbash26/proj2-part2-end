#include "MySerialServer.h"
#include "../lib/net/TimeoutException.h"

#include <unistd.h>

#include <cstring>
#include <sstream>

struct thread_params {
    net::Connection *conn;
    server_side::ClientHandler *ch;
};

void *thread_func(void *arg) {
    struct thread_params *params = (struct thread_params *) arg;

    // open the connection - and obtain an acceptor
    net::Acceptor acceptor = params->conn->open();

    while (true) {
        try {
            // accept a connection
            net::Socket clientSocket = acceptor.accept(20);

            //handle the client
            params->ch->handleClient(clientSocket);

        } catch (const net::TimeoutException &timeout) {
            // if timeout occured - print that it happened, and exit
            printf("%s - not accepting more clients. you can stop the server now :)\n", timeout.what());
            break;
        } catch (const std::string &err) {
            // if other error occured (syscall err etc) - print and exit
            printf("Fatal error: %s\nNot accepting any more clients...\n", err.c_str());
            break;
        }
    }

    delete params;
}


/*
 * this func open thread .
 */
void server_side::MySerialServer::open(uint16_t port, server_side::ClientHandler *ch) {
    c = new net::Connection(port, 32);

    // leave the listen and accept things to the thread.
    // therefore we need the sockfd in the thread. save it in the args.

    struct thread_params *args = new thread_params();
    // init the thread arguments (thread params)
    args->ch = ch;
    args->conn = c;
    // done initializing the thread arguments - create and start the thread.

    if (pthread_create(&tid, NULL, thread_func, args)) {
        throw std::string("Error creating server thread");
    }
}


void server_side::MySerialServer::stop(bool force) {
    if (!force) {
        // first - close the thread.
        printf("[server]: waiting for thread to stop...\n");
        if (pthread_join(tid, NULL)) {
            throw std::string("Error waiting to client handling thread to finish");
        }
        printf("[server]: client thread stopped...\n");
    } else {
        //force close the thread
        if (pthread_cancel(tid)) {
            throw std::string("Error killing connection thread");
        }
    }

    c->close();
    delete c;
}