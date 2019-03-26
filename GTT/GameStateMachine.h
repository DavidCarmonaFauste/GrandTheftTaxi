#pragma once
#include "GameState.h"
#include <stack>
#include "Constants.h"


using namespace std;

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	void setState(const string &s);
	map <string, GameState*> STATES_;

	string get_CurrentStateName() const;
	GameState* get_CurrentState();
	void initStates();


protected:
	string currentState_;

};

