//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_FILECACHEMANAGER_H
#define PROJ2_FILECACHEMANAGER_H

#include <map>
#include "CacheManager.h"
// hello
// call me

namespace server_side {
    template<class Problem, class Solution>
    class MyTestCacheManager : public CacheManager<Problem, Solution> {
    private:
        std::map<Problem, Solution> mem;

    public:
        MyTestCacheManager() {}

        ~MyTestCacheManager() {}


        bool containsSolution(const Problem &p) const override {
            return mem.count(p) > 0;
        }

        void saveSolution(const Problem &p, Solution &s) override {
            mem[p] = s;
        }

        Solution &loadSolution(const Problem &p) override {
            if (!containsSolution(p)) {
                throw "No solution found";
            }
            return (mem[p]);
        }
    };
}

#endif //PROJ2_FILECACHEMANAGER_H
