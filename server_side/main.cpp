#include <signal.h>
#include <stdlib.h>

#include <iostream>
#include "MySerialServer.h"
#include "client_handlers/MyTestClientHandler.h"
#include "../lib/algo/solvers/StringReverser.h"


// for closing when receiving sigint
server_side::Server *globalServer;

void sig_handler(int sig) {
    printf("got signal...\n");
    if (globalServer) {
        globalServer->stop(true);
        exit(1);
    }
}

int main(int argc, char **argv) {
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, nullptr);
    sigaction(SIGTERM, &act, nullptr);
    sigaction(SIGKILL, &act, nullptr);
    try {
        server_side::Server *server = new server_side::MySerialServer();
        globalServer = server;
        Solver<std::string, std::string> *solver = new StringReverser();
        server_side::ClientHandler *handler = new server_side::MyTestClientHandler(solver);
        server->open(8000, handler);

        std::string s;
        std::cout << "Server is running on port 8000, press 's' then enter to stop\n";
        std::cin >> s;
        server->stop();
        delete server;
        std::cout << "Server stopped.\n";
    } catch (const std::string &err) {
        printf("Catched %s...", err.c_str());
        exit(1);
    }
    return 0;
}