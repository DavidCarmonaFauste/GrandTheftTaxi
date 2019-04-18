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

	void start();
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual bool receiveEvent(Event& e);
	virtual ~TaxiSoundManagerCP();

	//void PlaySound(soundId id);
private:
	SoundManager* s_;
	Vehicle* v_;

	int channel_1; //workSound
	int channel_2; //acelerationSound
	int channel_3; //running speed

	int count_1;


	
};

