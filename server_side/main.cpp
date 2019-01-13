#include <signal.h>
#include <stdlib.h>

#include <iostream>
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "../lib/algo/search/Searchable.h"
#include "../lib/algo/search/Solution.h"
#include "../lib/algo/search/AStar.h"
#include "../lib/algo/search/SearcherAdapter.h"
#include "client_handlers/MyClientHandler.h"


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
        server_side::Server *server = new server_side::MyParallelServer();
        globalServer = server;
        Searcher *searcher = new AStar();
        SearcherAdapter *adapter = new SearcherAdapter(searcher);
        server_side::ClientHandler *handler = new server_side::MyClientHandler(adapter);
        server->open(8000, handler);

        std::string s;
        std::cout << "Server is running on port 8000, press 's' then enter to stop\n";
        std::cin >> s;
        server->stop();

        delete handler;
        delete adapter;
        delete searcher;
        delete server;
        std::cout << "Server stopped.\n";
    } catch (const std::string &err) {
        printf("Catched %s...", err.c_str());
        exit(1);
    }
    return 0;
}