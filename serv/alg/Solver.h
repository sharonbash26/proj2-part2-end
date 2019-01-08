//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_SOLVER_H
#define PROJ2_SOLVER_H

namespace server_side {
    template <class Problem, class Solution>
    class Solver {
    public:
        virtual Solution solve(Problem p) = 0;
    };

}
#endif //PROJ2_SOLVER_H
