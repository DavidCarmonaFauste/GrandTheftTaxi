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
	
	vector <int> channels_;
	int NUM_CHANNELS_; //hay que pasarla como const global

	int ch_3_Vol_;
	bool ch_3MaxVel;
	bool ch_3KeyDown;
	bool ch_3KeyUp;

	bool ch_5KeyUp;

	int ch_4_Vol_;

};

