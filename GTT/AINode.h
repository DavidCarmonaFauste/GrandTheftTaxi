#pragma once
#include <vector>
#include "TileMap.h"
#include <map>

using namespace std;

enum NodeType {
	EMPTY_NODE,
	COLLISION_NODE
};

static map<NodeType, int> costs{
	{EMPTY_NODE, 0},
	{COLLISION_NODE, 999}
};

// Struct of directions the path can take
struct dir {
public:
	dir(int x_, int z_){
		x = x_;
		z = z_;
	}
	int x;
	int z;
};

static dir dirs[] = { dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1) };

class AINode {
public:
	AINode();
	virtual ~AINode();

	static vector<vector<AINode*>> getNodesFromTilelayer(TileMap* tilemap);

	const Vector2D &getCoordinates() const { return coordinates_; };
	const NodeType &getNodeType() const { return nodeType_; };
	AINode* &getParent() { return parent_; };
	void setParent(AINode* parent) { parent_ = parent; };

	const int getH() const { return h_; };
	const int getG() const { return g_; };
	const int getF() const { return f_; };

	const int setH(int h) const { h = h_; };
	const int setG(int g) const { g = g_; };
	const int setF(int f) const { f = f_; };


private:
	Vector2D coordinates_;
	NodeType nodeType_;
	AINode* parent_;

	int h_;
	int g_;
	int f_;
};

