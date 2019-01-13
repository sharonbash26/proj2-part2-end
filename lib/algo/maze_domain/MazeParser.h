//
// Created by sharon_i4 on 09/01/2019.
//

#ifndef PROJ2_MAZEPARSER_H
#define PROJ2_MAZEPARSER_H


#include "Maze.h"

class MazeParser {
public:
    // parse maze suppoed to parse the strings that were inputted from the client
    // into a maze object.
    //  can later use the maze object - because it saves the data with numbers
    // but we get strings through the socket. lines for the matrix, then entry and dest cells

    // parseMaze takes that strings, and creates a maze object.
    // parseCell takes a string which representing a cell and turns it into a cell (which contains 2 numbers - row and coll)
    // thats it. you can look on the implementation in the cpp file.
    static Maze parseMaze(const std::vector<std::string> &lines, const std::string &entry, const std::string &dest);

    static Cell parseCell(const std::string &str);

};


#endif //PROJ2_MAZEPARSER_H
