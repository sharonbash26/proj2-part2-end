//
// Created by sharon_i4 on 08/01/2019.
//

#ifndef PROJ2_ACCEPTOR_H
#define PROJ2_ACCEPTOR_H


#include "Socket.h"

namespace net {
    class Acceptor {
    public:
        explicit Acceptor(int sockfd);

        Socket* accept(int timeout = 0);

    private:
        int sockfd;
    };
}

#endif //PROJ2_ACCEPTOR_H
