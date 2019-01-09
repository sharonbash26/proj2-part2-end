//
// Created by sharon_i4 on 08/01/2019.
//

#include <unistd.h>
#include <sys/socket.h>
#include "Socket.h"

#define BUFSIZE 256

net::Socket::Socket(int fd) {
    _fd = fd;
}

net::Socket::~Socket() {
    printf("Socket fd %d destructing...\n", _fd);
    if (close(_fd)) {
        throw std::string("Error while closing the socket");
    }
}

std::string net::Socket::readLine() {
    char buf[BUFSIZE] = {0};
    ssize_t msglen;
    std::string str;

    // step 1 - check if internal buffer already contains \n
    //printf("[readline]: looking for newline in internal buffer\n");
    size_t loc = _internal_buf.find('\n');
    if (loc == std::string::npos) {
        //printf("[readline]: not found newline.. starting to read.\n");
        // then no line inside the string.
        // read everything into the buffer, then if no newline found, read again.
        // until we se a newline. then we copy the contents of the internal buffer(until the newline)
        str += _internal_buf;
        _internal_buf.clear();
        bool found_newline_in_msg = false;

        //printf("[realine]: reading...\n");
        while (!found_newline_in_msg && (msglen = read(_fd, buf, BUFSIZE)) > 0) {
            // append the buffer into the string
            //printf("[readline]: read.\n");
            for (int i = 0; i < msglen; ++i) {
                if (buf[i] == '\n') {
                    found_newline_in_msg = true;
                    continue;
                }
                if (found_newline_in_msg) {
                    _internal_buf += buf[i];
                } else {
                    str += buf[i];
                }
            }
        } // while
        //printf("[readline] done reading\n");

        if (msglen < 0) {
            perror("Socket readLine");
            throw std::string("Error while reading from socket");
        }
        return std::move(str);
    }

    // else - found newline in the internal buffer. do not read from the socket - there is no need.
    // we already have a line in our buffer, just extract it from there and return it
    // the new line is in the position 'loc'

    //012345
    //ABCD_E
    str = _internal_buf.substr(0, loc);
    _internal_buf.erase(0, loc + 1);
    return std::move(str);
}

void net::Socket::send(const std::string &s) {
    const char *msg_to_client = s.c_str();
    if (write(_fd, msg_to_client, s.length()) < s.length()) {
        perror("Socket write");
        throw std::string("Error while writing to socket");
    }
}




