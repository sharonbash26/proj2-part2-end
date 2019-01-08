//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_MYSERIALSERVER_H
#define PROJ2_MYSERIALSERVER_H

#include "Server.h"
#include <pthread.h>
#include <pthread.h>

#define END_TOKEN ("end")

namespace server_side {

    class MySerialServer : public Server {
    public:
        void open(int port, ClientHandler *ch) override;

        void stop() override;

    private:
        int sockfd;
        pthread_t tid;
    };
}

#endif //PROJ2_MYSERIALSERVER_H
