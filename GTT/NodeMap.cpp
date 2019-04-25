#include "NodeMap.h"



NodeMap::NodeMap()
{
}

void NodeMap::addNode(Node* n, string id)
{
	if (!nodeExists(id))
		nodes[id] = n;
}

void NodeMap::addPatrol(vector<Node*> patrol, string id)
{
	patrols[id] = patrol;
}


void NodeMap::connectNodes(string id1, string id2)
{
	if (nodeExists(id1) && nodeExists(id2)) {
		Node* n1 = nodes[id1];
		Node* n2 = nodes[id2];
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


bool NodeMap::nodeExists(string id)
{
	for (auto o : nodes) {
		if (o.first == id) return true;
	}
	return false;
}

bool NodeMap::nodeExists(Node* n)
{
	for (auto o : nodes) {
		if (o.second == n) return true;
	}
	return false;
}
Node * NodeMap::getNearestNode(Vector2D position)
{
	Node* ret=nullptr;
	int minDistance = -1;
	int distance = 0;
	for (auto n : nodes) {
		distance = (pow(n.second->position_.x - position.x, 2) + pow(n.second->position_.y - position.y, 2));
		if (minDistance == -1 || distance < minDistance) {
			minDistance =distance;
			ret = n.second;
		}
	}
	return ret;
}

bool NodeMap::FindRoute(Node * current, Node * destiny, vector<Node*>& route, vector<Node*>& currentroute, int distance, int& minDistance)
{
	if (current == destiny) 
		return true;
	if (!nodeExists(destiny)) 
		return false;
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
	if (currentroute.empty()) return false;
	else return true;
}

map<string, Node*> NodeMap::getNodes()
{
	return nodes;
}

vector<Node*> NodeMap::getPatrol(string id)
{
	return patrols[id];
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

