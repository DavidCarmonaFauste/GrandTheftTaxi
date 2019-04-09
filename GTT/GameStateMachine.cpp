#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "MainState.h"
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
	// Mpeg state
	STATES_.insert(std::pair<string, GameState*>(NAME_MPEG_STATE, new MpegState(Game::getInstance()->getWindow(), Game::getInstance()->getRenderer())));
	//asigna valor string al atributo privado de la clase para gestionar el cambio de estado unav vez finalizado la reproducción 
	MpegState* intro = static_cast<MpegState*>(STATES_[NAME_MPEG_STATE]);
	intro->setVideoId(INTRO_VIDEO);
	
	
	//primer estado al ejectuar app
	setState(NAME_MPEG_STATE);


	//DEPURACION
	//setState(NAME_MAINMENU_STATE);
	//setState(NAME_MAIN_STATE);
}
