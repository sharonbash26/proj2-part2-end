cmake_minimum_required(VERSION 3.8)
project(proj2)

set(CMAKE_CXX_STANDARD 14)

set(NET lib/net/Socket.cpp lib/net/Socket.h
        lib/net/Acceptor.cpp lib/net/Acceptor.h
        lib/net/Connection.cpp lib/net/Connection.h
        lib/net/Acceptor.cpp lib/net/Acceptor.h
        lib/net/TimeoutException.h)

set(ALGO lib/algo/Solver.h
        lib/algo/CacheManager.h
        lib/algo/MapCacheManager.h
        lib/algo/solvers/StringReverser.h lib/algo/solvers/StringReverser.cpp
        lib/algo/maze_domain/Maze.h lib/algo/maze_domain/Maze.cpp lib/algo/maze_domain/Cell.h lib/algo/maze_domain/MazeParser.cpp lib/algo/maze_domain/MazeParser.h)

set(UTIL lib/util/Util.h lib/util/Util.cpp)

set(SERVER_FILES server_side/Server.h server_side/MySerialServer.cpp server_side/MySerialServer.h
        server_side/client_handlers/ClientHandler.h server_side/client_handlers/MyTestClientHandler.cpp server_side/client_handlers/MyTestClientHandler.h

        server_side/client_handlers/MyClientHandler.cpp server_side/client_handlers/MyClientHandler.h server_side/MyParallelServer.cpp server_side/MyParallelServer.h)

set(SOURCE_FILES server_side/main.cpp ${SERVER_FILES} ${NET} ${ALGO} ${UTIL})
add_executable(proj2 ${SOURCE_FILES})

add_executable(client client/client_main.cpp)