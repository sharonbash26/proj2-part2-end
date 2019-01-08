//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_MYSERIALSERVER_H
#define PROJ2_MYSERIALSERVER_H

#include "Server.h"
#include "../lib/net/Connection.h"
#include <pthread.h>
#include <pthread.h>

namespace server_side {
    class MySerialServer : public server_side::Server {
    public:
        void open(uint16_t port, server_side::ClientHandler *ch) override;

        void stop(bool force = false) override;

    private:
        net::Connection *c;
        pthread_t tid;
    };
}

#endif //PROJ2_MYSERIALSERVER_H
