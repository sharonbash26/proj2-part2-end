//
// Created by sharon_i4 on 09/01/2019.
//

#ifndef PROJ2_MYPARALLELSERVER_H
#define PROJ2_MYPARALLELSERVER_H

#include <vector>
#include "Server.h"
#include "../lib/net/Connection.h"

namespace server_side {
    class MyParallelServer : public Server{

    public:
        MyParallelServer();
        virtual ~MyParallelServer();

        void open(uint16_t port, server_side::ClientHandler *ch) override;

        void stop(bool force = false) override;

    private:
        net::Connection *c;
        pthread_mutex_t mtx;
        std::vector<pthread_t> threads;
        pthread_t tid;
    };
}

#endif //PROJ2_MYPARALLELSERVER_H
