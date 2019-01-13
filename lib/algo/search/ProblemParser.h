//
// Created by sharon_i4 on 13/01/2019.
//

#ifndef PROJ2_PROBLEMPARSER_H
#define PROJ2_PROBLEMPARSER_H


#include <string>
#include "Problem.h"

class ProblemParser {
public:
    static Problem *parseProblem(const std::vector<std::string> &lines, const std::string &in, const std::string &out);
};


#endif //PROJ2_PROBLEMPARSER_H
