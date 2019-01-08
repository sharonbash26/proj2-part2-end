#ifndef PROJ2_MYTESTCLIENTHANDLER_H
#define PROJ2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "alg/Solver.h"
#include "alg/CacheManager.h"
#include "alg/MyTestCacheManager.h"

namespace server_side {
    class MyTestClientHandler : public ClientHandler {
    public:
        explicit MyTestClientHandler(Solver<std::string, std::string> *solver);

        void handleClient(const std::string &in, std::ostream &out);
    private:
        Solver<std::string, std::string> *_solver;
        CacheManager<std::string, std::string> *_cacheManager;
    };
}


#endif //PROJ2_MYTESTCLIENTHANDLER_H
