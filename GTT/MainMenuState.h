#pragma once
#include "GameState.h"
#include "Vehicle.h"
#include "Button.h"


static void mockCallback () {
}

static void exitGameCallback () {
	Game::getInstance ()->setGameEnd ();
}

static void mainStateCallback () {
	Game::getInstance()->setState(NAME_MAIN_STATE);
}


class MainMenuState :
	public GameState
{
public:

	MainMenuState();
	virtual ~MainMenuState();

	virtual void start();

	virtual void update (Uint32 deltaTime);
	

private:
	
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

	//scene management
	int cont_1;
	
};

