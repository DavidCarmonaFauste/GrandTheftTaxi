#pragma once
#include "LogicComponent.h"
#include "NodeMap.h"
#include <vector>

class PhysicObject;

class IApatrol :
	public LogicComponent
{
public:
	IApatrol(PhysicObject* ph, NodeMap* districtMap, int patrolSpeed, vector<Node*> route = vector<Node*>());
	virtual void update(GameObject* o, Uint32 deltaTime);
	void setPause(bool pause);
	void setPatrol(bool patrol);
	virtual ~IApatrol();

private:
	bool alreadyAtDestination(GameObject* o);
	void Go(GameObject* o);
	void GoInBetweenNodes(GameObject* o);
	bool arrivedAtDestination(GameObject* o);
	void setNextDestination(Node* n);
	void AssignPlayerRoute(GameObject* o);
	void FollowPlayer(GameObject* o);
	void FollowRoute(GameObject* o);
	bool VehiclePosChanged();
	bool OutOfRoute(vector<Node*> route, int progress);
	bool inBetweenNodesFollow_;
	NodeMap* districtMap_;
	vector<Node*> patrolRoute_;
	vector<Node*> followRoute_;
	int followProgress_;
	int patrolProgress_;
	Node* currentNode_;
	Node* lastNode_;
	PhysicObject* phyO_;	
	bool paused_;
	bool patrol_;//si es true sigue la ruta establecida, si no sigue al taxi
	Vector2D destination_;
	Vector2D direction_;
	int patrolSpeed_;
};

