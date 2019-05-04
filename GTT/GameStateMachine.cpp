#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "MainState.h"
#include "ShopState.h"
#include "Reticule.h"



GameStateMachine::GameStateMachine() {

	currentState_ = "default";
}

GameStateMachine::~GameStateMachine() {
	for (auto state : STATES_) {
		delete state.second; state.second = nullptr;
	}
}

void GameStateMachine::setState(const string &s) {
	if (currentState_ != "default") 
		STATES_[currentState_]->end();

	currentState_ = s;

	STATES_[currentState_]->start();
}


string GameStateMachine::get_CurrentStateName() const {
	return currentState_;
}

GameState * GameStateMachine::get_CurrentState()  {
	return STATES_[currentState_];
}

void GameStateMachine::initStates() {
	// Main menu
	STATES_.insert(std::pair<string, GameState*>(NAME_MAINMENU_STATE, new MainMenuState()));
	// Main game
	STATES_.insert(std::pair<string, GameState*>(NAME_MAIN_STATE, new MainState()));
	// Shop state
	STATES_.insert(std::pair<string, GameState*>(NAME_SHOP_STATE, new ShopState()));
	
		
	//primer estado al ejectuar app
	//...

	//DEPURACION
	//setState(NAME_MAINMENU_STATE);
	setState(NAME_MAIN_STATE);
}
