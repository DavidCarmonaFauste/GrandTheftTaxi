#pragma once
#include "LogicComponent.h"

// AKA: GASOLINA
class Health : public LogicComponent {
public:
	Health(void(*callback)() = nullptr);
	virtual ~Health();

	virtual void update(GameObject* o, Uint32 deltaTime) override;

	int getHealth();
	void damage(int damage);
	void heal(int heal);

	// Are you sure you want to use this instead
	// 'heal()' or 'damage()'?
	void setHealth(int health);

	// The callback to be called every time the
	// health changes
	void setCallback(void (*callback)());

private:
	int health_;
	void (*callback_)() = nullptr;
};

