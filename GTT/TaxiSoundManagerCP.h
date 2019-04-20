#pragma once
#include "LogicComponent.h"
#include "SoundManager.h"
#include "Observer.h"

#include <map>

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

	//Channels 
	int channel_1; //start engine
	int channel_2; //regular engine
	int channel_3; //aceleration 
	int channel_4; //deceleration 
	int channel_5; //fast drive
	int channel_6; //drift
	

	int ch_2_Vol_; 
	int ch_3_Vol_;
	int ch_4_Vol_;
	int ch_6_Vol_;

	bool ch_3KeyDown;
	bool ch_3KeyUp;
	bool ch_5KeyUp;
	bool ch_6_KeyDown;
	bool ch_6_KeyUp;

	bool DEBUG_;

	

};

