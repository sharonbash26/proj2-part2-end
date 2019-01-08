cmake_minimum_required(VERSION 3.8)
project(proj2)

set(CMAKE_CXX_STANDARD 14)

set(SERVER_FILES serv/Server.h serv/MySerialServer.cpp serv/MySerialServer.h
        serv/ClientHandler.h serv/MyTestClientHandler.cpp serv/MyTestClientHandler.h
        serv/alg/Solver.h serv/alg/Solver.h serv/alg/CacheManager.h
        serv/alg/MyTestCacheManager.h
        serv/alg/StringReverser.h serv/alg/StringReverser.cpp)

set(SOURCE_FILES serv/main.cpp ${SERVER_FILES})
add_executable(proj2 ${SOURCE_FILES})

add_executable(client client/client_main.cpp)