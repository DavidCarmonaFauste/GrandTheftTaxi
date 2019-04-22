#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

#include "Game.h"

using namespace std;

typedef unsigned int uint;

int main(int argc, char* argv[]) {

	Game::getInstance()->initInstance(); //initInstance() only once
	Game::getInstance()->run();
	return 0;
}