#pragma once

#include <stack>
#include "Resources.h"
#include "VideoState.h"


class GameState;

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

