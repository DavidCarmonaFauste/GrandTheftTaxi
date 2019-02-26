#pragma once
#include "LogicComponent.h"

// AKA: GASOLINA
class Health : public LogicComponent {
public:
	Health();
	virtual ~Health();

	virtual void update(GameObject* o, Uint32 deltaTime) override;

	int getHealth();
	void damage(int damage);
	void heal(int heal);

	// Are you sure you want to use this instead
	// 'heal()' or 'damage()'?
	void setHealth(int health);

private:
	int health_;
};

