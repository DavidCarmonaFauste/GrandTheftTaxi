#include "IApatrol.h"
#include "PhysicObject.h"
#include "Vehicle.h"

IApatrol::IApatrol(PhysicObject * ph, GameObject* o, NodeMap * districtMap, int patrolSpeed, vector<Node*> route)
{
	phyO_ = ph;
	districtMap_ = districtMap;
	patrolSpeed_ = patrolSpeed;
	patrol_ = route;
	nextNode_ = nullptr;
	o_ = o;
}

void IApatrol::update(GameObject* o, Uint32 deltaTime)
{
	if (!started_) {
		goTo(districtMap_->getNearestConnectedNode(o->getCenter()));
		patrolProgress_ = -1;
		routeProgress_ = 0;
		started_ = true;
	}
	else {
		if (arrivedAtNode()) {
			int i;
			if (patrolProgress_ ==-1 && isPatrolNode(i)) {
				patrolProgress_ = (i + 1) % patrol_.size();
				
				route_ = AssignRoute(nextNode_, patrol_[patrolProgress_]);
				routeProgress_ = 0;
			}
			else if(patrolProgress_==-1) {
				route_ = AssignRoute(nextNode_, patrol_[patrolProgress_++]);
				routeProgress_ = 0;
			}
			else if(atNextPatrolNode()) {
				patrolProgress_ = (patrolProgress_ + 1) % patrol_.size();
				route_ = AssignRoute(nextNode_, patrol_[patrolProgress_]);
				routeProgress_ = 0;
			}
			
			goTo(route_[routeProgress_]);
			routeProgress_++;
			cout << patrolProgress_ << endl;
		}
	}
}

IApatrol::~IApatrol()
{
}

void IApatrol::goTo(Node * n)
{
	nextNode_ = n;
	Vector2D direction_ = Vector2D(n->position_.x - o_->getCenter().x, n->position_.y - o_->getCenter().y);
	direction_.Normalize();
	if (direction_.x != 0 || direction_.y != 0) {
		float angle = atan2f(-direction_.x, direction_.y);
		angle += 90.0 / 180.0*M_PI;
		phyO_->getBody()->SetTransform(phyO_->getBody()->GetPosition(), angle);
	}
	phyO_->getBody()->SetLinearVelocity(Vector2D(direction_.x * patrolSpeed_, direction_.y * patrolSpeed_));
}

bool IApatrol::arrivedAtNode()
{
	return(nextNode_->position_.x <= o_->getCenter().x + 5 && nextNode_->position_.x >= o_->getCenter().x - 5 &&
		nextNode_->position_.y <= o_->getCenter().y + 5 && nextNode_->position_.y >= o_->getCenter().y - 5);
}

bool IApatrol::isPatrolNode(int& a)
{
	for (int i = 0; i < patrol_.size(); i++) {
		if (nextNode_ == patrol_[i]) {
			a = i;
			return true;
		}
	}
	return false;
}

bool IApatrol::atNextPatrolNode()
{
	return nextNode_==patrol_[patrolProgress_];
}


vector<Node*> IApatrol::AssignRoute(Node * current, Node * destination)
{
	vector<Node*> route;
	vector<Node*> v;
	int minDistance = -1;
	districtMap_->FindRoute(current, destination, route, v, 0, minDistance);
	return route;
}

