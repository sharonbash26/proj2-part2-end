//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_SERVER_H
#define PROJ2_SERVER_H

#include "ClientHandler.h"

namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *ch) = 0;

        virtual void stop() = 0;
    };
}

#endif //PROJ2_SERVER_H
