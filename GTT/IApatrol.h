#pragma once
#include "LogicComponent.h"
#include "NodeMap.h"
#include <vector>

class PhysicObject;

class IApatrol :
	public LogicComponent
{
public:
	IApatrol(PhysicObject* ph, GameObject* o, NodeMap* districtMap, int patrolSpeed, vector<Node*> route = vector<Node*>());
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~IApatrol();

private:
	void SetDestination(Node* n);
	bool arrivedAtDestination();

	GameObject* o_;
	NodeMap* districtMap_;
	vector<Node*> patrolRoute_;
	PhysicObject* phyO_;
	Node* destination_;
	int patrolSpeed_;
	int patrolProgress_;

	bool goingToNode_;
	bool paused_;
};

