#include "IApatrol.h"
#include "PhysicObject.h"

IApatrol::IApatrol(PhysicObject * ph, NodeMap * districtMap, int patrolSpeed)
{
	phyO_ = ph;
	districtMap_ = districtMap;
	route_ = nullptr;
	currentNode_ = nullptr;
	lastNode_ = nullptr;
	destinated_ = false;
	paused_ = false;
	patrolSpeed_ = patrolSpeed;
}

void IApatrol::update(GameObject* o, Uint32 deltaTime)
{
	if (!paused_) {
		if (destinated_) {
			if (arrivedAtDestination(o))
				setNextDestination(o);
		}
		else 
			setNextDestination(o);

		Go(o);
	}
	else phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
}

void IApatrol::setPause(bool pause)
{
	paused_ = pause;
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
	return ((direction_.x < 0 && o->getCenter().x <= destination_.x)
		|| (direction_.x > 0 && o->getCenter().x >= destination_.x)
		|| (direction_.y < 0 && o->getCenter().y <= destination_.y)
		|| (direction_.y > 0 && o->getCenter().y >= destination_.y));
}

void IApatrol::setNextDestination(GameObject* o)
{
	if (currentNode_ == nullptr) {//beggining node
		currentNode_ = districtMap_->getNearestNode(o->getCenter());
		lastNode_ = currentNode_;
		destination_ = currentNode_->position_;
		destinated_ = true;
		//setNextDestination(o);
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
}
