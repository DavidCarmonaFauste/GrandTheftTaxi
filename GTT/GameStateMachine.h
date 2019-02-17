#pragma once

#include <stack>
#include <cstdlib>

using namespace std;
typedef unsigned int uint;

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	void handleEvents(uint deltaTime);
	void render(uint deltaTime) const;

	/*void pushState(states state);
	void swapStates(GameState* nState);
	void popState();
	void pop_nStates(GameState* elem);
	GameState* get_CurrentState() const;
	GameState* get_PreviousState() const;
	GameState* get_nState(GameState* state) const;*/


protected:
	//gestión de estados mediante pila
	//stack <states> containerStack_;
	


};

