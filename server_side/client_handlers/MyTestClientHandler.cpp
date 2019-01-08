//
// Created by sharon_i4 on 04/01/2019.
//

#include "MyTestClientHandler.h"

server_side::MyTestClientHandler::MyTestClientHandler(Solver<std::string, std::string> *solver) {
    _solver = solver;
    _cacheManager = new MapCacheManager<std::string, std::string>();
}


void server_side::MyTestClientHandler::handleClient(net::Socket &s) {
    std::string line;
    while (true) {
        //Receive a message from client, and handle it
        printf("[ClientHandler]: Reading a line...\n");
        line = s.readLine();
        printf("[ClientHandler]: done reading a line: '%s'\n", line.c_str());

        // if we should end the connection
        if(line == "end"){
            break;
        }

        // first ew check if the solution -exist if no :solve the solution and give the solution
        //out this is strem. into out se write the solution. the out we give to client .
        //containSolution this func that check if the we have soilution .

        printf("[ClientHandler]: handling client request: %s\n", line.c_str());
        if (_cacheManager->containsSolution(line)) {
            printf("[ClientHandler]: Found solution in cache.\n");
            s.send(_cacheManager->loadSolution(line));
            return;
        }

        printf("[ClientHandler]: Solving the problem.\n");
        std::string solution = _solver->solve(line);
        _cacheManager->saveSolution(line, solution);
        s.send(solution);
    }
}

