#pragma once
#include "GameState.h"
#include "Resources.h"

#include <stack>


using namespace std;

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	void setState(const string &s);

	string get_CurrentStateName() const;
	GameState* get_CurrentState() const;


protected:
	string currentState_;

};

