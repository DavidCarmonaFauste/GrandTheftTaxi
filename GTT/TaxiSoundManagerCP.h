#pragma once
#include "LogicComponent.h"
#include "SoundManager.h"

class Vehicle;

class TaxiSoundManagerCP :
	public LogicComponent
{
public:
	TaxiSoundManagerCP(Vehicle* v);
	void Start();
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~TaxiSoundManagerCP();
private:
	Vehicle* v_;
	SoundManager* s_;
};

