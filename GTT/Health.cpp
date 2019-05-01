#include "Health.h"

Health::Health(int maxHealth) {
	maxHealth_ = maxHealth;
	health_ = maxHealth;
}

Health::~Health() {

}

void Health::update(GameObject * o, Uint32 deltaTime) {
	damageOverTime(deltaTime);
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

void Health::setDamageOverTime(int damage, int frequency) {
	damageOverTimeValue_ = damage;
	damageFrequency_ = frequency;
}

void Health::resetHealth() {
	setHealth(maxHealth_);
}

void Health::setHealth(int health) {
	// Send an event about the health change
	HealthChangedEvent e(this, health, health_, maxHealth_);
	broadcastEvent(e);

	health_ = health;
}

void Health::increaseMaxHealth()
{
	maxHealth_ += HP_INCREASE;
}

bool Health::receiveEvent(Event& e) {
	if (e.type_ == RESPAWNED)
		resetHealth();

	return true;
}

void Health::damageOverTime(Uint32 deltaTime) {
	if (damageFrequency_ <= 0 && damageOverTimeValue_ == 0)
		return;

	damageTimer_ += deltaTime;
	while (damageTimer_ >= damageFrequency_) {
		damage(damageOverTimeValue_);
		damageTimer_ -= damageFrequency_;
	}
}
