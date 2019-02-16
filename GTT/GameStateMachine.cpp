#include "GameStateMachine.h"



GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

//agrega a la pila el estado pasado por parámetro
/*void GameStateMachine::pushState(GameState* state)
{
	pila_gameStates.push(state);
}*/
//si la pila no está vacía, se borra el estado y se elimina de la pila
/*void GameStateMachine::popState()
{
	if (!pila_gameStates.empty())
	{
		delete pila_gameStates.top();
		pila_gameStates.pop();
	}
}*/

//busca y devuelve un elem de la pila
/*GameState* GameStateMachine::get_nState(GameState* state) const {
	if (!pila_gameStates.empty())
		return pila_gameStates.nElem(state);
	else
		return nullptr;
}*/

//devuelve el actual estado de la pila
/*GameState* GameStateMachine::get_CurrentState() const {
	if (!pila_gameStates.empty())
		return pila_gameStates.top();
	else
		return nullptr;
}*/

//Cominca con Aplication: HandleEvents.
void GameStateMachine::handleEvents(uint deltaTime) {

}

//comunica con el estado acutal: render; si la pila no está vacía. 
void GameStateMachine::render(uint deltaTime) const {

}
