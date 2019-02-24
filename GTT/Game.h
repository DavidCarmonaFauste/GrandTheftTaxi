#pragma once

#include "SDL.h"
#include <map>




using namespace std;
typedef unsigned int uint;

// Forward declarations
class Animation;
class Camera;
enum cameraType;


class GameStateMachine;
class VideoState;
class Sprite;

class Game {
public:
	Game(SDL_Window *window_, SDL_Renderer *renderer_);
	virtual ~Game();

	bool update(Uint32 deltaTime);
	bool handleEvents(Uint32 deltaTime);
	void render(Uint32 deltaTime);

	//void run(uint deltaTime);
	//bool exitGame();

	static SDL_Renderer *renderer_;
	static SDL_Window *window_;
	static map<cameraType, Camera*> cameras_;

private:
	bool exit_ = false;

	//provisional
	//se instancia en clase Game.h y se gestiona render, update y handleEvent de los estados en pila 
	GameStateMachine* gmStMachine_;
	VideoState* videoIntro_;
};

