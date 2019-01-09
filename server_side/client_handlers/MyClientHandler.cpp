//
// Created by sharon_i4 on 08/01/2019.
//

#include <vector>
#include "MyClientHandler.h"
#include "../../lib/algo/MapCacheManager.h"
#include "../../lib/algo/maze_domain/MazeParser.h"

server_side::MyClientHandler::MyClientHandler(Solver<Maze, std::string> *solver) {
    this->solver = solver;
    cacheManager = new MapCacheManager<size_t, std::string>();
}

void server_side::MyClientHandler::handleClient(net::Socket *s) {
    std::string all_client_input;
    std::string line;
    std::vector<std::string> matrix;
    size_t problemHash;

    // read the matrix
    while (true) {
        //Receive a message from client, and handle it
        //printf("[ClientHandler]: Reading a line...\n");
        line = s->readLine();
        // if we should end the connection
        if (line == "end") {
            break;
        }
        matrix.push_back(line);
        all_client_input += line;
        all_client_input += '\n';
    }

    // now input the begin point and end point
    std::string begin = s->readLine();
    std::string end = s->readLine();

    all_client_input += begin;
    all_client_input += '\n';
    all_client_input += end;

    problemHash = hasher(all_client_input);
    all_client_input.clear();
    // now we got our problem hash.;
    if (cacheManager->containsSolution(problemHash)) {
        s->send(cacheManager->loadSolution(problemHash));
    } else {
        // otherwise - we need to solve the problem.
        // first of all - util the input into the matrix object.
        Maze m = MazeParser::parseMaze(matrix, begin, end);
        std::string sol = solver->solve(m);
        cacheManager->saveSolution(problemHash, sol);
        s->send(sol); // send the solution back to the client.
    }

    delete s; // delete the socket
}
