#include "GameStateMachine.h"



GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

//agrega a la pila el estado pasado por parámetro
void GameStateMachine::pushState(GameState* state)
{
	gameState_.push(state);
}
//si la pila no está vacía, se borra el estado y se elimina de la pila
void GameStateMachine::popState()
{
	if (!gameState_.empty())
	{
		delete gameState_.top();
		gameState_.pop();
	}
}


//devuelve el actual estado de la pila
GameState* GameStateMachine::get_CurrentState() const {
	if (!gameState_.empty())
		return gameState_.top();
	else
		return nullptr;
}


void GameStateMachine:: handleEvents(Uint32 deltaTime, SDL_Event& event) {
	GameState* currentState = get_CurrentState();
	currentState->handleEvents(deltaTime, event);
}

//comunica con el estado acutal: render; si la pila no está vacía. 
void GameStateMachine::render(Uint32 deltaTime) const {
	if (!gameState_.empty()) {
		GameState* currentState = get_CurrentState();
		currentState->render(deltaTime);
	}
}
