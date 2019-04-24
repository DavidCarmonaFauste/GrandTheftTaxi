#include "NodeMapsManager.h"
#include <string>
#include <iostream>

unique_ptr<NodeMapsManager> NodeMapsManager::instance_ = nullptr;


void NodeMapsManager::addNodeMap(string key, NodeMap * nodemap)
{
	nodemaps_[key] = nodemap;
}

bool NodeMapsManager::NodeMapExists(string key)
{
	for (auto o : nodemaps_) {
		if (o.first == key) return true;
	}
	return false;
}

void NodeMapsManager::ReadNodeMapsInfo()
{
	nodemapsFile_.open("../TextFiles/Nodes.txt");
	if (nodemapsFile_.is_open()) {
		string district;
		nodemapsFile_ >> district;
		for (int i = 0; i < 4; i++) {
			ConnectNodes(district);
		}
		nodemapsFile_.close();
	}
}

NodeMap * NodeMapsManager::getNodeMap(string key)
{
	return nodemaps_[key];
}

void NodeMapsManager::ConnectNodes(string d)
{
	string bNode;
	string connection;
	nodemapsFile_ >> bNode;
	for (int i = 0; i < 4; i++) {
		nodemapsFile_ >> connection;
		nodemaps_[d]->connectNodes(bNode, connection);
	}
}

NodeMapsManager::NodeMapsManager()
{
}


NodeMapsManager::~NodeMapsManager()
{
}
