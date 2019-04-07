#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "MainState.h"
#include "ShopState.h"
#include "MpegState.h"
#include "Reticule.h"



GameStateMachine::GameStateMachine() {

}

GameStateMachine::~GameStateMachine() {
	
}

void GameStateMachine::setState(const string &s) {
	if (currentState_ != "") STATES_[currentState_]->end();
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

	// Mpeg state
	STATES_.insert(std::pair<string, GameState*>(NAME_MPEG_STATE, new MpegState(Game::getInstance()->getWindow(), Game::getInstance()->getRenderer())));

	MpegState* intro = static_cast<MpegState*>(STATES_[NAME_MPEG_STATE]);
	intro->setVideoId(INTRO_VIDEO);
	//setState(NAME_MPEG_STATE);

	setState(NAME_MAINMENU_STATE);
	//setState(NAME_MAIN_STATE);
}
