//
// Created by sharon_i4 on 08/01/2019.
//
#include <netdb.h>

#include "Acceptor.h"
#include "TimeoutException.h"


net::Acceptor::Acceptor(int sockfd) {
    this->sockfd = sockfd;
}

net::Socket* net::Acceptor::accept(int timeout) {
    if (timeout > 0) {
        // no timeout
        fd_set set;
        struct timeval t;
        int rv;

        FD_ZERO(&set); /* clear the set */
        FD_SET(sockfd, &set); /* add our file descriptor to the set */
        t.tv_sec = timeout;
        t.tv_usec = 0; // this is 0 because all the internet examples showed that.


        // printf("[Acceptor]: Waiting for %d seconds for the next client\n", (int) t.tv_sec);
        rv = select(sockfd + 1, &set, NULL, NULL, &t);
        if (rv == -1) {
            perror("select");
            throw std::string("Error while trying to wait for connection (select)");
        } else if (rv == 0) {
            throw TimeoutException();
        }
    } // if timeout was set.


    // printf("[Acceptor] accepting a client...\n");
    int clientfd;
    socklen_t addr_len;
    struct sockaddr_in cli_addr;
    addr_len = sizeof(struct sockaddr_in);
    clientfd = ::accept(sockfd, (struct sockaddr *) &cli_addr, &addr_len);
    if (clientfd < 0) {
        // if accept failed stop accepting clients. (may be changed - but its simplest currently)
        perror("accept");
        throw std::string("Error while accepting a connection");
    }
    // printf("[Acceptor]: Successfully accepter the client, fd: %d\n", clientfd);
    return new Socket(clientfd);
}
