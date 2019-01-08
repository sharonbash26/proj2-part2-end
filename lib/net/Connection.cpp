
#include <netdb.h>
#include <string>
#include <strings.h>
#include "Connection.h"

net::Connection::Connection(uint16_t port, unsigned int queueSize) {
    opened = false;
    closed = false;

    qsize = queueSize;

    // setup the net
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::string("ERROR opening net");
    }
    bzero((char *) &serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw std::string("ERROR on binding");
    }
}

net::Connection::~Connection() {
    if (!opened) {
        // decide what to do with the port
    } else {
        // server was opened.
        // check if it was already closed.
        if (!closed) {
            close();
        }
    }
}

net::Acceptor net::Connection::open() {
    listen(sockfd, qsize);
    opened = true;

    // actually calls the acceptor constructor,
    // this is a syntax because the type (acceptor) is defined in the function name
    // its called initialized_list
    return net::Acceptor(sockfd);
}

void net::Connection::close() {
    if (shutdown(sockfd, 2)) {
        throw std::string("Failed to close the server net");
    }
    closed = true;
}