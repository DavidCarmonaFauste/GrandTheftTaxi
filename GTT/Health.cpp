#include "Health.h"

Health::Health(void(*callback)()) {

}

Health::~Health() {

}

void Health::update(GameObject * o, Uint32 deltaTime) {

}

int Health::getHealth() {
	return health_;
}

void Health::damage(int damage) {
	health_ -= damage;
}

void Health::heal(int heal) {
	health_ += heal;
}

void Health::setHealth(int health) {
	health_ = health;
}

void Health::setCallback(void(*callback)()) {
	callback_ = callback;
}
