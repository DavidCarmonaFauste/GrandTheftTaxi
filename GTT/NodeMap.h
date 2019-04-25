#pragma once
#include "Vector2D.h"
#include <vector>
#include <map>

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
	void addNode(Node* n, string id);
	void addPatrol(vector<Node*> patrol, string id);
	void connectNodes(string id1, string id2);
	bool nodeExists(string id);
	bool nodeExists(Node* n);
	Node* getNearestNode(Vector2D position);
	bool FindRoute(Node* current, Node* destiny, vector<Node*>& route, vector<Node*>&currentroute, int distance, int& minDistance);
	map<string, Node*> getNodes();
	vector<Node*> getPatrol(string id);
	virtual ~NodeMap();
private:
	map<string, Node*>nodes;//contiene todos los nodos del distrito con un identificador
	map<string, vector<Node*>> patrols;//diccionario de patrullas posibles del distrito
	bool hasNode(vector<Node*>&v, Node* n);
	int getDistance(Node* a, Node* b);
};

