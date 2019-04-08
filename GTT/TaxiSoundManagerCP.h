#pragma once
#include "LogicComponent.h"
#include "SoundManager.h"
#include "Observer.h"

class Vehicle;

class TaxiSoundManagerCP :
	public LogicComponent, public Observer
{
public:
	TaxiSoundManagerCP(Vehicle* v);
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual bool receiveEvent(Event& e);
	virtual ~TaxiSoundManagerCP();
private:
	SoundManager* s_;
	Vehicle* v_;
	int channel_;
};

