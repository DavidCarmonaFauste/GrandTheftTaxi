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
	void goTo(Node* n);
	bool arrivedAtNode();
	bool isPatrolNode(int& a);
	bool atNextPatrolNode();
	vector<Node*> AssignRoute(Node* current, Node* destination);

	GameObject* o_;
	NodeMap* districtMap_;
	vector<Node*> patrol_;
	vector<Node*> route_;
	PhysicObject* phyO_;
	Node* nextNode_;
	int patrolSpeed_;
	int patrolProgress_;
	int routeProgress_;

	bool started_ = false;
};

