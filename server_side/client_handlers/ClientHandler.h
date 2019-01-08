//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_CLIENTHANDLER_H
#define PROJ2_CLIENTHANDLER_H

#include <iostream>
#include "../../lib/net/Socket.h"

namespace server_side {
    class ClientHandler {
    public:
        virtual void handleClient(net::Socket &s) = 0;
    };
}

#endif //PROJ2_CLIENTHANDLER_H
