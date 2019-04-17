#include "NodeMap.h"



NodeMap::NodeMap()
{
}

void NodeMap::addNode(Node* n)
{
	nodes.push_back(n);
	for (int i = 0; i < 4; i++) {
		if (n->connections_[i] != nullptr) {
			switch (i) {
				case NORTH:
					if(nodeExists(n->connections_[i]))
					n->connections_[i]->connections_[SOUTH] = n;
					break;
				case SOUTH:
					n->connections_[i]->connections_[NORTH] = n;
					break;
				case EAST:
					n->connections_[i]->connections_[WEST] = n;
					break;
				case WEST:
					n->connections_[i]->connections_[EAST] = n;
					break;
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

vector<Node*> NodeMap::getNodes()
{
	return nodes;
}


NodeMap::~NodeMap()
{
}

