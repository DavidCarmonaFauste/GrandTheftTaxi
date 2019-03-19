#pragma once
#include "LogicComponent.h"
#include "Observer.h"

// AKA: GASOLINA
class Health :	public LogicComponent,
				public Observable,
				public Observer {
public:
	Health(int maxHealth);
	virtual ~Health();

	virtual void update(GameObject* o, Uint32 deltaTime) override;

	int getHealth();
	int getMaxHealth();
	void damage(int damage);
	void heal(int heal);

	// Sets the current health to the maximum health
	void resetHealth();

	// Are you sure you want to use this instead
	// 'heal()' or 'damage()'?
	void setHealth(int health);

	virtual bool receiveEvent(Event &e) override;

private:
	int maxHealth_;
	int health_;
};

