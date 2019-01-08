#ifndef PROJ2_MYTESTCLIENTHANDLER_H
#define PROJ2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../../lib/algo/Solver.h"
#include "../../lib/algo/CacheManager.h"
#include "../../lib/algo/MapCacheManager.h"

namespace server_side {
    class MyTestClientHandler : public ClientHandler {
    public:
        explicit MyTestClientHandler(Solver<std::string, std::string> *solver);

        void handleClient(net::Socket &s) override;

    private:
        Solver<std::string, std::string> *_solver;
        CacheManager<std::string, std::string> *_cacheManager;
    };
}


#endif //PROJ2_MYTESTCLIENTHANDLER_H
