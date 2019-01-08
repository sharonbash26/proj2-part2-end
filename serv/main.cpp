#include <iostream>

#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "alg/StringReverser.h"

int main(int argc, char** argv){
    try {
        server_side::Server *server = new server_side::MySerialServer();
        server_side::Solver<std::string, std::string> *solver = new server_side::StringReverser();
        server_side::ClientHandler *handler = new server_side::MyTestClientHandler(solver);
        server->open(8000, handler);

        std::string s;  
        std::cout << "Server is running on port 8000, press 's' then enter to stop\n";
        std::cin >> s;
        server->stop();
        std::cout << "Server stopped.\n";
    }catch(const char* e){
        printf("Catched %s...", e);
        exit(1);
    }
    return 0;
}