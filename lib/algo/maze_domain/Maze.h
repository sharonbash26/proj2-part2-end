//
// Created by sharon_i4 on 08/01/2019.
//

#ifndef PROJ2_MAZE_H
#define PROJ2_MAZE_H


#include <string>
#include <vector>
#include "Cell.h"

class Maze {
public:
    Maze(size_t nrows, size_t ncols, Cell entry, Cell dest);

    virtual ~Maze();

    int getWeightAt(const Cell &cell) const;
    void setWeightAt(const Cell &cell, int weight);

    bool isInRange(const Cell &cell) const;

    /*
    static Maze deserialize(std::vector<std::vector<std::string>> matrix,
                            std::vector<std::string> entry, std::vector<std::string> dest);
    */
protected:
    void assertInRange(const Cell &cell) const;

private:
    size_t nrows, ncols;
    int **cells;
    Cell entry, dest;

};


#endif //PROJ2_MAZE_H
