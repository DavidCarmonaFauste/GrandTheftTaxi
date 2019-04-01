#include "Trigger.h"

Trigger::Trigger(int w, int h, int x, int y) {
	width_ = w; height_ = h;
	position_ = Vector2D(x, y);

	phyO_ = new PhysicObject(b2_kinematicBody, w, h, x, y);
	phyO_->setSensor(true);
	addLogicComponent(phyO_);
}


Trigger::~Trigger() {
	Container::~Container();
	delete phyO_; phyO_ = nullptr;
}

PhysicObject * Trigger::getPhysicsObject() {
	return phyO_;
}

void callback() {

}