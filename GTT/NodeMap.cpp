#include "NodeMap.h"



NodeMap::NodeMap()
{
}

void NodeMap::addNode(Node* n)
{
	if(!nodeExists(n))
		nodes.push_back(n);

	cout<<nodes.size()<< endl;
}

void NodeMap::connectNodes(Node * n1, Node * n2)
{
	if (nodeExists(n1) && nodeExists(n2)) {
		if (n2->position_.x == n1->position_.x) {
			if (n2->position_.y < n1->position_.y) {
				n1->connections_[NORTH] = n2;
				n2->connections_[SOUTH] = n1;
			}
			else if (n2->position_.y > n1->position_.y) {
				n1->connections_[SOUTH] = n2;
				n2->connections_[NORTH] = n1;
			}
		}
		else if (n2->position_.y == n1->position_.y) {
			if (n2->position_.x > n1->position_.x) {
				n1->connections_[EAST] = n2;
				n2->connections_[WEST] = n1;
			}
			else if (n2->position_.x < n1->position_.x) {
				n1->connections_[WEST] = n2;
				n2->connections_[EAST] = n1;
			}
		}
		else
			cout << "incompatible nodes: " << "n1= (" << n1->position_.x << ", " << n1->position_.y << ") " << "n2= (" << n2->position_.x << ", " << n2->position_.y << ")" << endl;
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

