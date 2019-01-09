#include "MyParallelServer.h"


#include "../lib/net/TimeoutException.h"

#include <unistd.h>

#include <cstring>
#include <sstream>

server_side::MyParallelServer::MyParallelServer() {
    pthread_mutex_init(&mtx, 0);
}

server_side::MyParallelServer::~MyParallelServer() {
    pthread_mutex_destroy(&mtx);
}

struct accept_thread_params {
    pthread_mutex_t *mtx;
    std::vector<pthread_t> *threads;

    net::Connection *conn;
    server_side::ClientHandler *ch;
};

struct client_thread_params {
    client_thread_params(net::Socket *_s, server_side::ClientHandler *_ch) : s(_s), ch(_ch) {}

    net::Socket *s;
    server_side::ClientHandler *ch;
};

//this func run the fread of the clien
void *client_func(void *arg) {
    client_thread_params *params = (client_thread_params *) arg;
    params->ch->handleClient(params->s);
    delete params;
    return nullptr;
}

static void *accept_loop(void *arg) {
    accept_thread_params *params = (accept_thread_params *) arg;

    // open the connection - and obtain an acceptor
    net::Acceptor acceptor = params->conn->open();

    while (true) {
        try {
            // found the problem - the socket is getting destructed. searching solution now in my pc
            // the easiest solution is to return pointer to socket instead of object.
            // therefore we will need to change the clientHandler, but its not a big issue.
            printf("[Server]: accepting client...\n");
            // accept a connection
            net::Socket *clientSocket = acceptor.accept(20);
            printf("[Server]: accepted. creating client thread params...\n");
            client_thread_params *client_args = new struct client_thread_params(clientSocket, params->ch);
            printf("[Server]: done creating params. Creating thread...\n");
            pthread_t client_tid;
            if (pthread_create(&client_tid, NULL, client_func, client_args)) {
                throw std::string("Failed to craete client thread");
            }
            printf("[Server]: done. adding thread to threads vector\n");
            pthread_mutex_lock(params->mtx);
            params->threads->push_back(client_tid);
            pthread_mutex_unlock(params->mtx);
            printf("[Server]: done. next..\n");
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
    return nullptr;
}

void server_side::MyParallelServer::open(uint16_t port, server_side::ClientHandler *ch) {
    c = new net::Connection(port, 32);

    // leave the listen and accept things to the thread.
    // therefore we need the sockfd in the thread. save it in the args.

    accept_thread_params *args = new accept_thread_params();
    // init the thread arguments (thread params)
    args->ch = ch;
    args->conn = c;
    args->mtx = &mtx;
    args->threads = &threads;
    // done initializing the thread arguments - create and start the thread.

    if (pthread_create(&tid, NULL, accept_loop, args)) {
        throw std::string("Error creating server thread");
    }
}

void server_side::MyParallelServer::stop(bool force) {

    bool err = false;
    if (!force) {
        // wait for all the client threads to finish
        printf("[server]: waiting for all client threads to stop...\n");
        pthread_mutex_lock(&mtx);
        for (pthread_t &t : threads) {
            if (pthread_join(t, NULL)) {
                err = true;
            }
        }
        pthread_mutex_unlock(&mtx);


        printf("[server]: waiting for main accept thread to stop...\n");
        if (pthread_join(tid, NULL)) {
            throw std::string("Error waiting to client handling thread to finish");
        }
        if (err) {
            throw std::string("failed to close one of the client threads");
        }
        printf("[server]: done :)\n");
    } else {
        pthread_mutex_lock(&mtx);
        for (pthread_t &t : threads) {
            if (pthread_cancel(t)) {
                err = true;
            }
        }
        pthread_mutex_unlock(&mtx);

        //force close the thread
        if (pthread_cancel(tid)) {
            throw std::string("Error killing connection thread");
        }
    }
    if (err) {
        throw std::string("failed to close one of the client threads");
    }

    c->close();
    delete c;
}


