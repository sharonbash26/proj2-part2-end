//
// Created by sharon_i4 on 04/01/2019.
//

#include "MyTestClientHandler.h"

server_side::MyTestClientHandler::MyTestClientHandler(server_side::Solver<std::string, std::string> *solver) {
    _solver = solver;
    _cacheManager = new MyTestCacheManager<std::string, std::string>();
}


void server_side::MyTestClientHandler::handleClient(const std::string &in, std::ostream &out) {
    // first ew check if the solution -exist if no :solve the solution and give the solution
    //out this is strem. into out se write the solution. the out we give to client .
    //containSolution this func that check if the we have soilution .

    printf("[ClientHandler]: handling client request: %s", in.c_str());
    if (_cacheManager->containsSolution(in)) {
        printf("[ClientHandler]: Found solution in cache.\n");
        out << _cacheManager->loadSolution(in);
        return;
    }

    printf("[ClientHandler]: Solving the problem.\n");
    std::string solution = _solver->solve(in);
    _cacheManager->saveSolution(in, solution);
    out << solution;
}

