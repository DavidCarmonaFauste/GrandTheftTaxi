#include "IApatrol.h"
#include "PhysicObject.h"
#include "Vehicle.h"

IApatrol::IApatrol(PhysicObject * ph, GameObject* o, NodeMap * districtMap, int patrolSpeed, vector<Node*> route): IAMovementBehaviour(ph, o, districtMap, patrolSpeed)
{
	patrol_ = route;
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

