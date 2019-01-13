#ifndef ASTAR_H
#define ASTAR_H

#include "Searcher.h"
#include "Searchable.h"
#include "Solution.h"
#include "State.h"

#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <limits>

class AStar : public Searcher
{
	
Searchable* searchable;
int numberOfNodesEvaluated;

public:
	AStar();
	Solution search(Searchable* _searchable);
	int getNumberOfNodesEvaluated();
	State popMinFValue(std::vector<State> opendList
			, std::map<std::string, double> fValueMap);
	bool isListContainItem(std::vector<State> list, State s);
	std::vector<State> removeStateFromList(std::vector<State> list, State s);
};

#endif
