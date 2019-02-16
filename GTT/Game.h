#pragma once

#include "SDL.h"
#include <map>

using namespace std;

// Forward declarations
class Animation;
class Camera;
enum cameraType;

class Sprite;

class Game {
public:
	Game(SDL_Window *window_, SDL_Renderer *renderer_);
	virtual ~Game();

	bool update(Uint32 deltaTime);
	bool handleEvents(Uint32 deltaTime);
	void render(Uint32 deltaTime);

	static SDL_Renderer *renderer_;
	static SDL_Window *window_;
	static map<cameraType, Camera*> cameras_;

private:
	bool exit_ = false;
};

