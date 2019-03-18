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
	Game::getInstance ()->setGameStart ();
}


class MainMenuState :
	public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();

};

