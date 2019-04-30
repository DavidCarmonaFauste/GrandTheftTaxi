#include "IApatrol.h"
#include "PhysicObject.h"
#include "Vehicle.h"

IApatrol::IApatrol(PhysicObject * ph, GameObject* o, NodeMap * districtMap, int patrolSpeed, vector<Node*> route)
{
	phyO_ = ph;
	districtMap_ = districtMap;
	patrolSpeed_ = patrolSpeed;
	patrolRoute_ = route;
	destination_ = nullptr;
	o_ = o;
}

void IApatrol::update(GameObject* o, Uint32 deltaTime)
{
	if (destination_==nullptr) {
		SetDestination(patrolRoute_[0]);
		patrolProgress_ = 0;
	}
	else {
		if (goingToNode_) {
			if (arrivedAtDestination()) {
				patrolProgress_ = (patrolProgress_ + 1) % patrolRoute_.size();
				SetDestination(patrolRoute_[patrolProgress_]);
			}
		}
		else {
			phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));

		}
	}

	
}

IApatrol::~IApatrol()
{
}

void IApatrol::SetDestination(Node* n)
{
	destination_ = n;
	Node* current=districtMap_->getNearestConnectedNode(o_->getCenter());
	if (!destination_->isConnected(current)) {
		vector<Node*> v;
		vector<Node*> a;
		int minDistance = -1;
		v.push_back(current);
		districtMap_->FindRoute(current, destination_, v, a, 0, minDistance);
		destination_ = v[0];
	}
	Vector2D direction = (n->position_ - o_->getCenter());
	direction.Normalize();
	phyO_->getBody()->SetLinearVelocity(Vector2D(direction.x * patrolSpeed_, direction.y * patrolSpeed_));
	goingToNode_ = true;
}

bool IApatrol::arrivedAtDestination()
{
	return o_->getCenter() == destination_->position_;
}

