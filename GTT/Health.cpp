#include "Health.h"

Health::Health(int maxHealth) {
	maxHealth_ = maxHealth;
	health_ = maxHealth;
}

Health::~Health() {

}

void Health::update(GameObject * o, Uint32 deltaTime) {

}

int Health::getHealth() {
	return health_;
}

int Health::getMaxHealth() {
	return maxHealth_;
}

void Health::damage(int damage) {
	setHealth(health_ - damage);
}

void Health::heal(int heal) {	
	setHealth(health_ + heal);
}

void Health::resetHealth() {
	health_ = maxHealth_;
}

void Health::setHealth(int health) {
	// Send an event about the health change
	HealthChangedEvent e(this, health, health_, maxHealth_);
	broadcastEvent(e);

	health_ = health;
}

bool Health::receiveEvent(Event& e) {
	if (e.type_ == RESPAWNED)
		resetHealth();

	return true;
}
