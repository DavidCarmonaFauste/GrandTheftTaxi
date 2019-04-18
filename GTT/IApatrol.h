#pragma once
#include "LogicComponent.h"
#include "NodeMap.h"
#include <vector>

class PhysicObject;

class IApatrol :
	public LogicComponent
{
public:
	IApatrol(PhysicObject* ph, NodeMap* districtMap, int patrolSpeed);
	virtual void update(GameObject* o, Uint32 deltaTime);
	void setPause(bool pause);
	virtual ~IApatrol();

private:
	void Go(GameObject* o);
	bool arrivedAtDestination(GameObject* o);
	void setNextDestination();
	NodeMap* districtMap_;
	vector<Node*>* route_;
	Node* currentNode_;
	Node* lastNode_;
	PhysicObject* phyO_;	
	bool destinated_;
	bool paused_;
	Vector2D destination_;
	Vector2D direction_;
	int patrolSpeed_;
};

