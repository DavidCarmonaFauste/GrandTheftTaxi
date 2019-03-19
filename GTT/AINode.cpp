#include "AINode.h"



AINode::AINode() {

}


AINode::~AINode() {

}

vector<vector<AINode*>> AINode::getNodesFromTilelayer(TileMap* tilemap) {
	vector<vector<AINode*>> nodes;
	vector<vector<Tile*>> collisionsLayer = tilemap->getLayer("Collisions");

	int y = 0;
	for (auto row : collisionsLayer) {
		int x = 0;

		nodes.push_back(vector<AINode*>());
		for (auto tile : row) {
			AINode* n = new AINode();

			if (tile != nullptr) {
				n->coordinates_ = Vector2D(x, y);
				n->nodeType_ = tile->getPhysicObject() == nullptr ? EMPTY_NODE : COLLISION_NODE;
			}

			nodes.back().push_back(n);
			x++;
		}
		y++;
	}

	return nodes;
}