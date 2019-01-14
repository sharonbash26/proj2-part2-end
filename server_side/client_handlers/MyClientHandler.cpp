//
// Created by sharon_i4 on 08/01/2019.
//

#include <vector>
#include "MyClientHandler.h"
#include "../../lib/algo/MapCacheManager.h"
#include "../../lib/algo/search/ProblemParser.h"

server_side::MyClientHandler::MyClientHandler(SearcherAdapter *solver) {
    this->solver = solver;
    cacheManager = new MapCacheManager<size_t, std::string>();
}

void server_side::MyClientHandler::handleClient(net::Socket *s) {
    std::string all_client_input;
    std::string line;
    std::vector<std::string> matrix;
    size_t problemHash;


    printf("[ClientHandler]: reading matrix...\n");
    // read the matrix
    while (true) {
        //Receive a message from client, and handle it
        printf("[ClientHandler]: Reading a line...\n");
        line = s->readLine();
        // if we should end the connection
        if (line == "end") {
            break;
        }
        matrix.push_back(line);
        all_client_input += line;
        all_client_input += '\n';
    }
    printf("[ClientHandler]: done reading matrix. reading entry and end spot...\n");
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
        Searchable* maze = ProblemParser::parseProblem(matrix, begin, end);
        //Maze m = MazeParser::parseMaze(matrix, begin, end);
        Solution sol = solver->solve(maze);
        std::string solstr = sol.toString();
        cacheManager->saveSolution(problemHash, solstr);
        s->send(solstr); // send the solution back to the client.
    }

    delete s; // delete the socket
}
