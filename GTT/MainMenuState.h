#pragma once
#include "GameState.h"
#include "Vehicle.h"
#include "Button.h"


static void mockCallback () {
	cout << "button pushed\n";
}

static void exitGameCallback () {
	cout << "button pushed\n"; 
	Game::getInstance ()->setGameEnd ();
}

static void mainStateCallback () {
	cout << "button pushed\n"; 
	Game::getInstance()->setState(NAME_MAIN_STATE);
}


class MainMenuState :
	public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();

	virtual void update (Uint32 deltaTime);
	

private:
	Button* newGameButton_ = nullptr;
};

