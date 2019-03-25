#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include <Box2D/Box2D.h>
#include <map>
#include "GameState.h"
#include "Font.h"

using namespace std;


//static const string NAME_INTRO_STATE = "introState";
static const string NAME_MAINMENU_STATE = "mainMenuState";
static const string NAME_MAIN_STATE = "MAIN_STATE";

class Resources
{
public:
	static Resources* getInstance();
	void initStates();

	map <string, GameState*> STATES_;


private:
	// Singleton instance
	static Resources *singleton_;

	Resources();
	virtual ~Resources();
};
