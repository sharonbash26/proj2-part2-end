//
// Created by sharon_i4 on 08/01/2019.
//

#include <stdexcept>
#include "Maze.h"

Maze::Maze(size_t nrows, size_t ncols, Cell entry, Cell dest) {
    this->nrows = nrows;
    this->ncols = ncols;
    this->entry = entry;
    this->dest = dest;

    this->cells = new int *[nrows];
    for (size_t i = 0; i < nrows; ++i) {
        this->cells[i] = new int[ncols];
        for (size_t j = 0; j < ncols; ++j) {
            this->cells[i][j] = 0;
        }
    }
}

Maze::~Maze() {
    for (size_t i = 0; i < nrows; ++i) {
        delete[] cells[i];
    }
    delete[] cells;
}

int Maze::getWeightAt(const Cell &cell) const {
    assertInRange(cell);
    return cells[cell.row][cell.col];

}

void Maze::setWeightAt(const Cell &cell, int weight) {
    assertInRange(cell);
    cells[cell.row][cell.col] = weight;
}

bool Maze::isInRange(const Cell &cell) const {
    return cell.row < nrows && cell.col < ncols;
}

void Maze::assertInRange(const Cell &cell) const {
    if (!isInRange(cell)) {
        throw std::out_of_range("Cell out of range");
    }
}








