#include "admin.h"

int main () {


	std::cout<<"MATRIX IS:\n";

	std::vector<std::vector<std::string>> matrix;

	int k = 10;
/*
	for (int i = 0; i < 5; ++i) {
		std::vector<std::string> curLine;
		for (int i2 = 0; i2 < 5; ++i2) {
			curLine.push_back(std::to_string(++k));
			std::cout<<k<<" ";
		}
		matrix.push_back(curLine);

		std::cout<<"\n";
	}
*/

std::vector<std::string> curLine;
curLine.push_back("0");
curLine.push_back("21");
curLine.push_back("0");
curLine.push_back("1");
curLine.push_back("6");
matrix.push_back(curLine);
curLine.clear();

curLine.push_back("0");
curLine.push_back("21");
curLine.push_back("0");
curLine.push_back("100");
curLine.push_back("2");
matrix.push_back(curLine);
curLine.clear();

curLine.push_back("0");
curLine.push_back("90");
curLine.push_back("0");
curLine.push_back("0");
curLine.push_back("0");
matrix.push_back(curLine);
curLine.clear();

curLine.push_back("0");
curLine.push_back("0");
curLine.push_back("10");
curLine.push_back("10");
curLine.push_back("9");
matrix.push_back(curLine);
curLine.clear();

curLine.push_back("0");
curLine.push_back("0");
curLine.push_back("0");
curLine.push_back("2");
curLine.push_back("0");
matrix.push_back(curLine);
curLine.clear();
	
	Searchable* searchable = new Problem(matrix, "1,2", "4,3");

	std::cout<<"SOURCE IS "<<searchable->getInitialState().getState()<<"\n";
	std::cout<<"DETINATION IS "<<searchable->getGoalState().getState()<<"\n";

//	Searcher* searcher = new BreadthFirstSearch();
//	Searcher* searcher = new DepthFirstSearch();
//	Searcher* searcher = new BestFirstSearch();
	Searcher* searcher = new AStar();
	SearcherAdapter searchAdapter = SearcherAdapter(searcher);

	std::vector<std::string> optimalSolution = searchAdapter.solve(searchable).getOptimalPath();

	std::cout<<"The optimal path is:\n";
	for (int i = 0; i < optimalSolution.size(); ++i) {
		std::cout<<optimalSolution[i]<<"\n";
	}

	return 0;
}
