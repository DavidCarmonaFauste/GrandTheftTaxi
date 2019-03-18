#include "AINode.h"



AINode::AINode() {

}


AINode::~AINode() {

}

vector<vector<AINode*>> AINode::getNodesFromTilelayer(TileMap* tilemap) {
	vector<vector<AINode*>> nodes;

	vector<vector<Tile*>> collisionsLayer = tilemap->getLayer("Collisions");

	for (auto tile : collisionsLayer) {
		// Do things
	}

	return nodes;
}
