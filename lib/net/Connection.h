//
// Created by sharon_i4 on 08/01/2019.
//

#ifndef PROJ2_CONNECTION_H
#define PROJ2_CONNECTION_H


#include "Acceptor.h"

namespace net {

    class Connection {

    public:
        Connection(uint16_t port, unsigned int queueSize);

        ~Connection();

        Acceptor open();
        // u can call me, meanwhile im refactoring and implementing the matrix thing.
        // its simple to simulate the algo, and that is what i will probably do - supply a
        // fake solver which returns some random solution.

        void close();

    private:
        int sockfd;
        unsigned int qsize;
        bool opened, closed;
    };
}

#endif //PROJ2_CONNECTION_H
