#include "NodeMapsManager.h"

unique_ptr<NodeMapsManager> NodeMapsManager::instance_ = nullptr;


void NodeMapsManager::addNodeMap(string key, NodeMap * nodemap)
{
	(*nodemaps_)[key] = nodemap;
}

bool NodeMapsManager::NodeMapExists(string key)
{
	for (auto o : *nodemaps_) {
		if (o.first == key) return true;
	}
	return false;
}

NodeMap * NodeMapsManager::getNodeMap(string key)
{
	return (*nodemaps_)[key];
}

NodeMapsManager::NodeMapsManager()
{
	nodemaps_ = new map<string, NodeMap*>();
}


NodeMapsManager::~NodeMapsManager()
{
}
