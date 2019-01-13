//
// Created by sharon_i4 on 13/01/2019.
//

#include "ProblemParser.h"
#include "../../util/Util.h"

Problem *ProblemParser::parseProblem(const std::vector<std::string> &lines,
                                     const std::string &in, const std::string &out) {
    std::vector<std::vector<std::string>> matrix;
    for (const std::string &line : lines) {
        matrix.push_back(Util::split(line, ','));
    }
    return new Problem(matrix, in, out);
}
