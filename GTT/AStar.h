#pragma once
#include "AINode.h"
#include <cmath>

using namespace std;

class AStar {
public:
	AStar();
	virtual ~AStar();

	// Manhattan heuristic
	int ManhattanHeuristic(AINode* n, AINode* target);

	// Gets the adjacent nodes for the given node
	vector<dir> GetAdjacentNodes(AINode* node, int h);

private:
	int width, height;
};
