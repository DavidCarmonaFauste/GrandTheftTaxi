#pragma once

#include <stack>
#include "GameState.h"

using namespace std;

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	//void handleEvents(Uint32 deltaTime, SDL_Event& event);
	void render(Uint32 deltaTime) const;
	void pushState(GameState* state);
	void popState();

	GameState* get_CurrentState() const;



protected:
	//gestión de estados mediante pila
	stack <GameState*> gameState_;


	//previa inicialización de estados en un diccionario. 


	


};

