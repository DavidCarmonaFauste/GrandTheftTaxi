#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"
#include "SoundManager.h"




class MainMenuState :
	public GameState, public Observer
{
public:

	MainMenuState();
	virtual ~MainMenuState();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime);

	virtual bool receiveEvent(Event& e);


private:

	SoundManager* s_;

	map<string, int> Channels_;

	//Background
	Container* mainBackground_ = nullptr;

	//Buttons
	map<string, Button*> buttons_;

	soundId Sound_NewGameButton_;
	//taxi
	Container* Taxi_ = nullptr;
	Animation* Taxi_anm; //necesary for set in this Update
	//title
	Container* Title_ = nullptr;
	Animation* Title_anm; //necesary for set in this Update

	bool DEBUG_;


};