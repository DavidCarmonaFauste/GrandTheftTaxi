#pragma once
#include <vector>
#include "TileMap.h"

using namespace std;

class AINode {
public:
	AINode();
	virtual ~AINode();

	static vector<vector<AINode*>> getNodesFromTilelayer(TileMap* tilemap);
};

