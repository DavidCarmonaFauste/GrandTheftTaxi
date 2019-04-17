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

	int channel_; //workSound
	//int channel_2; //acelerationSound
	

	//count management
	int count_1; //start sound 
	int count_2; //gestion eventos 
	int count_3; // deceleration mode
	
};

