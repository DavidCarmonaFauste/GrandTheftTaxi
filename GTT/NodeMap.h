#pragma once
#include "Vector2D.h"
#include <vector>
enum Connections {
	NORTH,
	SOUTH,
	EAST,
	WEST
};
class Node {
public:
	Node(Vector2D pos, string id) {
		id_ = id;
		position_ = pos;
		for (int i = 0; i < 4; i++) {
			connections_[i] = nullptr;
		}
	}
	Vector2D position_;
	string id_;
	Node* connections_[4];
	bool isDeadEnd() {
		int count = 0;
		for (int i = 0; i < 4; i++) {
			if (connections_[i] != nullptr) {
				count++;
				if (count > 1) return false;
			}
		}
		return true;
	}
};
class NodeMap
{
public:
	NodeMap();
	void addNode(Node* n);
	void connectNodes(Node* n1, Node* n2);
	bool nodeExists(Node* node);
	Node* getNearestNode(Vector2D position);
	void FindRoute(Node* current, Node* destiny, vector<Node*>& route, vector<Node*>&currentroute, int distance, int& minDistance);
	vector<Node*> getNodes();
	virtual ~NodeMap();
private:
	vector<Node*>nodes;
	bool hasNode(vector<Node*>&v, Node* n);
	int getDistance(Node* a, Node* b);
};

