#include "NodeMapsManager.h"

unique_ptr<NodeMapsManager> NodeMapsManager::instance_ = nullptr;


void NodeMapsManager::addNodeMap(string key, NodeMap * nodemap)
{
	(*nodemaps_)[key] = nodemap;
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
