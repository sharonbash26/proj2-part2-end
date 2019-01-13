#include "AStar.h"

AStar::AStar() {
	this->numberOfNodesEvaluated = 0;
}

Solution AStar::search(Searchable* _searchable) {
	
	this->searchable = _searchable;

	std::vector<State> listOfNodes = searchable->getListOfStates();

	std::map<std::string, double> fValueMap;
	std::map<std::string, double> gValueMap;
	std::map<std::string, double> hValueMap;
	std::map<std::string, std::string> cameFromMap;

	for (int i = 0; i < listOfNodes.size(); i++) {
		gValueMap[listOfNodes[i].getState()] = 0;
		hValueMap[listOfNodes[i].getState()] = this->searchable
				->calculateHValue(listOfNodes[i]);

		std::numeric_limits<int> limits;
		fValueMap[listOfNodes[i].getState()] = limits.max();
	}

    std::vector<State> opendList;
	std::vector<State> closedList;

	gValueMap[this->searchable->getInitialState().getState()] = 0;
	fValueMap[this->searchable->getInitialState().getState()] = 
			hValueMap[this->searchable->getInitialState().getState()];

	cameFromMap[this->searchable->getInitialState().getState()] = "-1,-1";
	
	opendList.push_back(this->searchable->getInitialState());
	++this->numberOfNodesEvaluated;

	while (!opendList.empty()) {

		State curState = this->popMinFValue(opendList, fValueMap);
		opendList = this->removeStateFromList(opendList, curState);
		closedList.push_back(curState);
		std::vector<State> adj = this->searchable->getAllPossibleSDtates(curState);

		for (int i = 0; i < adj.size(); i++) {

			if (adj[i].isEqual(this->searchable->getGoalState())) {

				cameFromMap[adj[i].getState()] = adj[i].getCameFrom();

				std::string curStateStr = this->searchable->getGoalState().getState();
				std::string initStateStr = this->searchable->getInitialState().getState();

				std::vector<std::string> inversePath;

				while(curStateStr != initStateStr) {
					inversePath.push_back(curStateStr);
					curStateStr = cameFromMap[curStateStr];
				}

				std::vector<std::string> path;
				while(!inversePath.empty()) {
					path.push_back(inversePath[inversePath.size() - 1]);
					inversePath.pop_back();
				}

				curStateStr = this->searchable->getInitialState().getState();
				std::vector<std::string> directionPath;

				for(int i = 0; i < path.size(); i++) {
					directionPath.push_back(this->searchable
							->determineDirection(curStateStr, path[i]));
				
					curStateStr = path[i];
				}

				return Solution(directionPath);
			}

			double cost = gValueMap[curState.getState()] + adj[i].getCost();
			
			if (!this->isListContainItem(closedList, adj[i])) {

				if (this->isListContainItem(opendList, adj[i])
					&& (cost < gValueMap[adj[i].getState()])) {

					opendList = this->removeStateFromList(opendList, adj[i]);
				}

				else if (this->isListContainItem(closedList, adj[i])
						&& (cost < gValueMap[adj[i].getState()])) {

					closedList = this->removeStateFromList(closedList, adj[i]);
				}

				else if ((!this->isListContainItem(opendList, adj[i]))
						&& !this->isListContainItem(closedList, adj[i])) {

					opendList.push_back(adj[i]);
					gValueMap[adj[i].getState()] = cost;
					fValueMap[adj[i].getState()] = hValueMap[adj[i].getState()] 
							+ gValueMap[adj[i].getState()];
					cameFromMap[adj[i].getState()] = adj[i].getCameFrom();

					++this->numberOfNodesEvaluated;
				}
			}
		}
	}

	std::vector<std::string> optimalSolution;
	return Solution(optimalSolution);
}

std::vector<State> AStar::removeStateFromList(std::vector<State> list, State s) {

	int indexToRemove = -1;

	for (int i = 0; i < list.size(); i++) {
		if (list[i].getState() == s.getState()) {
			indexToRemove = i;
			break;
		}
	}	

	list.erase(list.begin() + indexToRemove);
	return list;
}

bool AStar::isListContainItem(std::vector<State> list, State s) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i].getState() == s.getState()) {
			return true;
		}
	}

	return false;
}

State AStar::popMinFValue(std::vector<State> opendList
		, std::map<std::string, double> fValueMap) {
	State minState = opendList[0];

	for (int i = 1; i < opendList.size(); i++) {
		if (fValueMap[opendList[i].getState()] 
					< fValueMap[minState.getState()]) {
			minState = opendList[i];
		}
	}

	return minState;
}
	
int AStar::getNumberOfNodesEvaluated() {
	return this->numberOfNodesEvaluated;
}
