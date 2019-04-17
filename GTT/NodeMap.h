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
	Node(Vector2D pos) {
		position_ = pos;
		for (int i = 0; i < 4; i++) {
			connections_[i] = nullptr;
		}
	}
	Vector2D position_;
	Node* connections_[4];
	bool isConnected() {
		for (int i = 0; i < 4; i++) {
			if (connections_[i] != nullptr) {
				return true;
			}
		}
		return false;
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
	vector<Node*> getNodes();
	virtual ~NodeMap();
private:
	vector<Node*>nodes;
};

