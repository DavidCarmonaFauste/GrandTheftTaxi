#include "NodeMap.h"



NodeMap::NodeMap()
{
}

void NodeMap::addNode(Node* n)
{
	if(!nodeExists(n))
		nodes.push_back(n);
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
	Node* ret=nodes[0];
	int minDistance = -1;
	int distance = 0;
	for (auto n : nodes) {
		distance = (pow(n->position_.x - position.x, 2) + pow(n->position_.y - position.y, 2));
		if (minDistance == -1 || distance < minDistance) {
			minDistance =distance;
			ret = n;
		}
	}
	return ret;
}

void NodeMap::FindRoute(Node * current, Node * destiny, vector<Node*>& route, vector<Node*>& currentroute, int distance, int& minDistance)
{
	for (auto c : current->connections_) {
		if (c != nullptr && !hasNode(currentroute, c)) {
			distance += getDistance(current, c);
			if (minDistance==-1 || distance<minDistance) {//la ruta aun no es mas larga de la ultima ruta valida
				if (c==destiny) {
					minDistance = distance;
					route = currentroute;
					route.push_back(c);
				}
				else {
					currentroute.push_back(c);
					FindRoute(c, destiny, route, currentroute, distance, minDistance);
					currentroute.pop_back();
					distance -= getDistance(current, c);
				}
			}
			else {
				distance -= getDistance(current, c);
			}
		}
	}
}

vector<Node*> NodeMap::getNodes()
{
	return nodes;
}


NodeMap::~NodeMap()
{
}

bool NodeMap::hasNode(vector<Node*>& v, Node* n)
{
	for (auto i : v) {
		if (i == n) return true;
	}
	return false;
}

int NodeMap::getDistance(Node * a, Node * b)
{
	double disX = a->position_.x - b->position_.x;
	double disY = a->position_.y - b->position_.y;

	return sqrt(pow(disX, 2) + pow(disY, 2));
}

