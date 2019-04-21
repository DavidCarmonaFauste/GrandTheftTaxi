#pragma once
#include "LogicComponent.h"
#include "NodeMap.h"
#include <vector>

class PhysicObject;

class IApatrol :
	public LogicComponent
{
public:
	IApatrol(PhysicObject* ph, NodeMap* districtMap, int patrolSpeed, vector<Node*>* route=nullptr);
	virtual void update(GameObject* o, Uint32 deltaTime);
	void setPause(bool pause);
	virtual ~IApatrol();

private:
	void Go(GameObject* o);
	bool arrivedAtDestination(GameObject* o);
	void setNextDestination(GameObject* o);
	void FollowPlayer(GameObject* o);
	NodeMap* districtMap_;
	vector<Node*>* patrolRoute_;
	vector<Node*> followRoute_;
	int followProgress_;
	int patrolProgress_;
	Node* currentNode_;
	Node* lastNode_;
	PhysicObject* phyO_;	
	bool destinated_;
	bool paused_;
	bool patrol_;//si es true sigue la ruta establecida, si no recorre los nodos de manera aleatoria
	Vector2D destination_;
	Vector2D direction_;
	int patrolSpeed_;
};

