//
// Created by sharon_i4 on 08/01/2019.
//

#ifndef PROJ2_MYCLIENTHANDLER_H
#define PROJ2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../../lib/algo/Solver.h"
#include "../../lib/algo/CacheManager.h"
#include "../../lib/algo/maze_domain/Maze.h"

namespace server_side {
    class MyClientHandler : public server_side::ClientHandler {
    public:
        explicit MyClientHandler(Solver<Maze, std::string> *solver);

        void handleClient(net::Socket *s) override;

    private:
        Solver<Maze, std::string> *solver;
        CacheManager<size_t, std::string> *cacheManager;

        std::hash<std::string> hasher;
    };
}

#endif //PROJ2_MYCLIENTHANDLER_H
