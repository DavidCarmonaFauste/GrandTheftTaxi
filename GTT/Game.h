#pragma once

#include "SDL.h"
#include "GameStateMachine.h"
#include <map>
#include <Box2D/Box2D.h>
#include "CameraType.h"
#include"Resources.h"


using namespace std;
typedef unsigned int uint;

// Forward declarations
class Animation;
class Camera;
class Sprite;
class Vehicle;
class SoundManager;
class TileMap;
class Gun;
class ShotGun;
class ProyectilePool;


class Game {
public:
	Game(SDL_Window *window_, SDL_Renderer *renderer_);
	virtual ~Game();

	bool update(Uint32 deltaTime);
	bool handleEvents(Uint32 deltaTime);
	void render(Uint32 deltaTime);

	void run(uint deltaTime);
	bool exitGame();

	static SDL_Renderer *renderer_;
	static SDL_Window *window_;
	static map<cameraType, Camera*> cameras_;

	static b2World* GetWorld();
	static SoundManager* getSoundManager();

private:
	static b2World* world_;
	static SoundManager* soundManager_;

	bool exit_ = false;


	Vehicle* taxi_;
	TileMap* tileMap_;
	Gun* gun_;
	ShotGun* shotgun_;

	//provisional
	//se instancia en clase Game.h y se gestiona render, update y handleEvent de los estados en pila 
	GameStateMachine* gmStMachine_;
};

