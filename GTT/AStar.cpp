#include "AStar.h"



AStar::AStar() {

}


AStar::~AStar() {

}

int AStar::ManhattanHeuristic(AINode * n, AINode * target) {
	return abs(target->getCoordinates().getX() - n->getCoordinates().getX())
		+ abs(target->getCoordinates().getY() - n->getCoordinates().getY()) * costs[n->getNodeType()];
}

vector<dir> AStar::GetAdjacentNodes(AINode * node, int h) {
	int nx, nz;
	vector<dir> adjacentCoords = vector<dir>();

	for (int i = 0; i < sizeof(dirs); i++) {
		nx = node->getCoordinates().getX() + dirs[i].x; nz = node->getCoordinates().getY() + dirs[i].z;
		if (nx >= 0 && nx < width && nz >= 0 && nz < height) {
			adjacentCoords.push_back(dir(nx, nz));
		}
	}
	return adjacentCoords;
}