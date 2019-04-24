#include "IApatrol.h"
#include "PhysicObject.h"
#include "Vehicle.h"

IApatrol::IApatrol(PhysicObject * ph, NodeMap * districtMap, int patrolSpeed, vector<Node*> route)
{
	phyO_ = ph;
	districtMap_ = districtMap;
	patrolRoute_ = route;
	currentNode_ = nullptr;
	lastNode_ = nullptr;
	paused_ = false;
	patrolSpeed_ = patrolSpeed;
	patrolProgress_ = 0;
	patrol_ = false;
}

void IApatrol::update(GameObject* o, Uint32 deltaTime)
{
	if (!paused_) {
		if (currentNode_ != nullptr) {
			if (patrol_) {
				if (arrivedAtDestination(o)) {
					FollowRoute();
				}
			}
			else if (arrivedAtDestination(o))
				FollowPlayer(o);
		}
		else 			
			setNextDestination((districtMap_->getNearestNode(o->getCenter())));

		Go(o);
	}
	else phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
}

void IApatrol::setPause(bool pause)
{
	paused_ = pause;
}

void IApatrol::setPatrol(bool patrol)
{
	if (patrol_ != patrol && !patrolRoute_.empty()) {
		patrol_ = patrol;
		patrolProgress_ = 0;
		followProgress_ = 0;
	}
}


IApatrol::~IApatrol()
{
}

void IApatrol::Go(GameObject * o)
{
	direction_ = Vector2D(destination_.x - o->getCenter().x, destination_.y - o->getCenter().y);
	direction_.Normalize();
	float angle = atan2f(-direction_.x, direction_.y);
	angle += 90.0 / 180.0*M_PI;
	phyO_->getBody()->SetTransform(phyO_->getBody()->GetPosition(), angle);
	phyO_->getBody()->SetLinearVelocity(Vector2D(direction_.x * patrolSpeed_, direction_.y * patrolSpeed_));
}

bool IApatrol::arrivedAtDestination(GameObject* o)
{
	return (direction_==Vector2D(0,0) 
		|| (direction_.x < 0 && o->getCenter().x <= destination_.x)
		|| (direction_.x > 0 && o->getCenter().x >= destination_.x)
		|| (direction_.y < 0 && o->getCenter().y <= destination_.y)
		|| (direction_.y > 0 && o->getCenter().y >= destination_.y));
}

void IApatrol::setNextDestination(Node* n)
{
	if (n != nullptr) {
		destination_ = n->position_;
		if (currentNode_ != nullptr) lastNode_ = currentNode_;
		currentNode_ = n;
	}

	/*if (currentNode_ == nullptr) {//beggining node
		currentNode_ = districtMap_->getNearestNode(o->getCenter());
		lastNode_ = currentNode_;
		destination_ = currentNode_->position_;
		destinated_ = true;
	}
	else {//decide next node
		if (!currentNode_->isDeadEnd() || lastNode_==currentNode_) {
			double a = rand() % 100;
			int c = a * 4 / 100.0;
			while (currentNode_->connections_[c] == nullptr || currentNode_->connections_[c]==lastNode_) {
				a = rand() % 100;
				c = a * 4 / 100.0;
			}
			lastNode_ = currentNode_;
			currentNode_ = currentNode_->connections_[c];
			destination_ = currentNode_->position_;
		}
		else {
			Node* aux;
			aux = lastNode_;
			lastNode_ = currentNode_;
			currentNode_ = aux;
			destination_ = currentNode_->position_;
			
		}
	}
	*/

}

void IApatrol::AssignPlayerRoute(GameObject * o)
{
	vector<Node*>route;
	int minDistance = -1;
	Node* taxiNode = districtMap_->getNearestNode(Vehicle::getInstance()->getCenter());
	setPatrol(!districtMap_->FindRoute(currentNode_, taxiNode, followRoute_, route, 0, minDistance));
	followProgress_ = 0;
}

void IApatrol::FollowPlayer(GameObject * o)
{
	if (followRoute_.empty() ||
		(!followRoute_.empty() && (VehiclePosChanged() || OutOfRoute(followRoute_, followProgress_)))) {
		AssignPlayerRoute(o);
	}
	else {
		setNextDestination(followRoute_[followProgress_]);
		followProgress_++;
	}
}

void IApatrol::FollowRoute()
{
	setNextDestination(patrolRoute_[patrolProgress_]);
	patrolProgress_ = (patrolProgress_ + 1) % patrolRoute_.size();
}

bool IApatrol::VehiclePosChanged()
{
	return followRoute_.back() != districtMap_->getNearestNode(Vehicle::getInstance()->getCenter());
}

bool IApatrol::OutOfRoute(vector<Node*> route, int progress)
{
	return(progress >= route.size() || (progress!=0 && route[progress] != currentNode_));
}
