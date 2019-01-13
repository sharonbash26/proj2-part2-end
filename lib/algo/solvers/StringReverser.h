//
// Created by sharon_i4 on 07/01/2019.
//

#ifndef PROJ2_STRINGREVERSESOLVER_H
#define PROJ2_STRINGREVERSESOLVER_H


#include <string>
#include "../Solver.h"

class StringReverser : public Solver<std::string, std::string> {
    std::string solve(std::string *p) override;
};


#endif //PROJ2_STRINGREVERSESOLVER_H
