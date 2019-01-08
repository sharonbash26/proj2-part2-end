//
// Created by sharon_i4 on 09/01/2019.
//

#include <algorithm>
#include "MazeParser.h"
#include "../../util/Util.h"

Maze MazeParser::parseMaze(const std::vector<std::string> &lines, const std::string &entry, const std::string &dest) {
    size_t nrows = lines.size();
    size_t ncols = (size_t) std::count(lines[0].begin(), lines[0].end(), ',') + 1;

    Cell entrycell = parseCell(entry);
    Cell destcell = parseCell(dest);

    Maze m(nrows, ncols, entrycell, destcell);

    std::vector<std::string> values;
    Cell c;
    for (size_t row = 0; row < nrows; ++row) {
        values = Util::split(lines[row], ',');
        if (ncols != values.size()) {
            throw std::string("bad format");
        }
        c.row = row;
        for (size_t col = 0; col < ncols; ++col) {
            c.col = col;
            m.setWeightAt(c, std::stoi(values[col]));
        }
    }
    return std::move(m);
}

Cell MazeParser::parseCell(const std::string &str) {
    std::vector<std::string> vals = Util::split(str, ',');
    if (vals.size() != 2) {
        throw std::string("Bad Cell Format!");
    }
    int n;
    Cell c;
    if ((n = std::stoi(vals[0])) < 0) {
        throw std::string("Bad Cell Format!");
    }
    c.row = (size_t) n;

    if ((n = std::stoi(vals[1])) < 0) {
        throw std::string("Bad Cell Format!");
    }
    c.col = (size_t) n;
    return std::move(c);
}
