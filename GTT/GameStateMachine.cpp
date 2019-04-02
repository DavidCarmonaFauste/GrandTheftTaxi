#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "MainState.h"



GameStateMachine::GameStateMachine() {
	currentState_ = NAME_MAINMENU_STATE;
	//currentState_ = NAME_MAIN_STATE;
}

GameStateMachine::~GameStateMachine() {
	
}

//agrega a la pila el estado pasado por par�metro
void GameStateMachine::setState(const string &s) {
	//el atributo de la clase recoge el valor del nuevo estado y el update se encarga de gestionarlo 
	currentState_ = s;
}


//devuelve el actual estado de la pila
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
}
