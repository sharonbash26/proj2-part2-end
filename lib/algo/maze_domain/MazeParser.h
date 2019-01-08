//
// Created by sharon_i4 on 09/01/2019.
//

#ifndef PROJ2_MAZEPARSER_H
#define PROJ2_MAZEPARSER_H


#include "Maze.h"

class MazeParser {
public:
    static Maze parseMaze(const std::vector<std::string> &lines, const std::string &entry, const std::string &dest);

    static Cell parseCell(const std::string &str);

};


#endif //PROJ2_MAZEPARSER_H
