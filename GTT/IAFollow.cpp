#include "IAFollow.h"
#include "Vehicle.h"
#include "EnemyManager.h"

IAFollow::IAFollow(PhysicObject * ph, GameObject * o, NodeMap * districtMap, int patrolSpeed, double followDistance) 
	:IAMovementBehaviour(ph, o, districtMap, patrolSpeed)
{
	followDistance_ = followDistance;
}

void IAFollow::update(GameObject * o, Uint32 deltaTime)
{
	if (followDistance_ == -1 || getDistanceToTaxi() <= followDistance_) {
		if (!started_) {
			goTo(districtMap_->getNearestConnectedNode(o_->getCenter()));
			if (arrivedAtNode()) {
				route_ = AssignRoute(nextNode_, districtMap_->getNearestConnectedNode(Vehicle::getInstance()->getCenter()));
				routeProgress_ = 0;
				started_ = true;
			}
		}
		else {
			if (arrivedAtNode()) {
				phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
				if (route_.empty() || route_.back() != districtMap_->getNearestConnectedNode(Vehicle::getInstance()->getCenter())) {
					route_ = AssignRoute(nextNode_, districtMap_->getNearestConnectedNode(Vehicle::getInstance()->getCenter()));
					routeProgress_ = 0;
				}
				if (!route_.empty() && routeProgress_ < route_.size()) {
					goTo(route_[routeProgress_]);
					routeProgress_++;
				}
			}
			else {
				if (EnemyManager::getInstance()->EnemyAtPos(nextNode_->position_, o_) && (o_->getCenter() - nextNode_->position_).Length() <= 32 * 3) {
					phyO_->getBody()->SetLinearVelocity(Vector2D());
				}
				else {
					goTo(nextNode_);
				}
			}
		}
	}
	else {
		started_ = false;
		phyO_->getBody()->SetLinearVelocity(Vector2D());
	}
	
}

IAFollow::~IAFollow()
{
}

double IAFollow::getDistanceToTaxi()
{
	return (Vehicle::getInstance()->getCenter() - o_->getCenter()).Length();
}
