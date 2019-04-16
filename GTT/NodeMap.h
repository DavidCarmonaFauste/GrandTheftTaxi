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
	Node(Vector2D pos, Node* north=nullptr, Node* south = nullptr, Node* east = nullptr, Node* west = nullptr) {
		position_ = pos;
		connections_[NORTH] = north;
		connections_[SOUTH] = south;
		connections_[EAST] = east;
		connections_[WEST] = west;
	}
	Vector2D position_;
	Node* connections_[4];
};
class NodeMap
{
public:
	NodeMap();
	void addNode(Node* node);
	bool nodeExists(Node* node);
	Node* getNearestNode(Vector2D position);
	virtual ~NodeMap();
private:
	vector<Node*>nodes;
};

