//
// Created by sharon_i4 on 04/01/2019.
//

#ifndef PROJ2_CACHEMANAGER_H
#define PROJ2_CACHEMANAGER_H


template<class Problem, class Solution>
class CacheManager {
public:
    virtual bool containsSolution(const Problem &p) const = 0;

    virtual void saveSolution(const Problem &p, Solution &s) = 0;

    virtual Solution &loadSolution(const Problem &p) = 0;

};

#endif //PROJ2_CACHEMANAGER_H
