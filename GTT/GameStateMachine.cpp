#include "GameStateMachine.h"




GameStateMachine::GameStateMachine() {
	currentState_ = NAME_MAINMENU_STATE;
	//currentState_ = NAME_MAIN_STATE;
}


GameStateMachine::~GameStateMachine() {
	
}

//agrega a la pila el estado pasado por parámetro
void GameStateMachine::setState(const string &s) {
	//el atributo de la clase recoge el valor del nuevo estado y el update se encarga de gestionarlo 
	currentState_ = s;
}


//devuelve el actual estado de la pila
string GameStateMachine::get_CurrentStateName() const {
	return currentState_;
}

GameState * GameStateMachine::get_CurrentState() const {
	return Resources::getInstance()->STATES_[currentState_];
}

