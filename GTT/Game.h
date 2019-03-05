#pragma once

#include "SDL.h"
#include <map>
#include <Box2D/Box2D.h>
#include "CameraType.h"
#include"Resources.h"




using namespace std;
typedef unsigned int uint;

// Forward declarations
class Animation;
class Camera;
enum cameraType;


class GameStateMachine;
class VideoState;
class Sprite;
class Vehicle;
class SoundManager;
class TileMap;


class Game {
public:
	//bool update(Uint32 deltaTime);
	
	//void render(Uint32 deltaTime);

	static Game* getInstance();

	void run();
	bool exitGame();

	void handleEvents(Uint32 deltaTime);
	void update(Uint32 deltaTime);
	void render(Uint32 deltaTime);

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

	//provisional
	//se instancia en clase Game.h y se gestiona render, update y handleEvent de los estados en pila 
	GameStateMachine* gmStMachine_;
	VideoState* videoIntro_;
	//*SDL_Event event; //PROVISIONAL, DEBE CAMBIRSE POR COMPONENTE F�SICAS

	static Game* singleton;
	Game();
	virtual ~Game();
};

