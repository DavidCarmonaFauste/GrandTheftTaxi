#include "NodeMap.h"



NodeMap::NodeMap()
{
}

void NodeMap::addNode(Node* node)
{
	if (!nodeExists(node)) {
		nodes.push_back(node);
		for (int i = 0; i < 4; i++) {
			if (node->connections_[i] != nullptr) {
				switch (i) {
					case NORTH:
						node->connections_[i]->connections_[SOUTH] = node;
						break;
					case SOUTH:
						node->connections_[i]->connections_[NORTH] = node;
						break;
					case EAST:
						node->connections_[i]->connections_[WEST] = node;
						break;
					case WEST:
						node->connections_[i]->connections_[EAST] = node;
						break;
				}
				addNode(node->connections_[i]);
			}
		}
	}
}

bool NodeMap::nodeExists(Node * node)
{
	for (auto o : nodes) {
		if (o == node) return true;
	}
	return false;
}

Node * NodeMap::getNearestNode(Vector2D position)
{
	return nullptr;
}


NodeMap::~NodeMap()
{
}
