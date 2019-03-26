#pragma once
#include "SDL.h"
#include <map>
#include <Box2D/Box2D.h>
#include "CameraType.h"
#include "Camera.h"
#include "SoundManager.h"
#include "GameStateMachine.h"


using namespace std;
typedef unsigned int uint;

class Game {
public:
	static Game* getInstance();

	void run();
	bool exitGame();


	//main methods
	void handleEvents(Uint32 deltaTime);
	void update(Uint32 deltaTime);
	void render(Uint32 deltaTime);

	//get Game SDL attributes
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	int getWindowWidth();
	int getWindowHeight();
	int getCameraHeight();
	int getCameraWidth();

	//get Game private attributes
	b2World* getWorld();
	SoundManager* getSoundManager();
	Camera* getCamera(cameraType cT);

	void init();

private:
	static Game* singleton_; //unique instance

	Game();
	virtual ~Game();

	const int winWidth_ = 1280;
	const int winHeight_ = 720;

	const int cameraWidth = 1600;
	const int cameraHeight = 900;

	//SDL Elements
	SDL_Renderer *renderer_;
	SDL_Window *window_;

	//Phsysics
	b2World* world_;

	//Media
	SoundManager* soundManager_;
	map<cameraType, Camera*> cameras_;

	//states
	GameStateMachine* gmStMachine_;
	bool exit_ = false;

	// Delta time and physics time management
	double accumulator_;
	double step_ = 1.0f / 60.0f;
	int velIterations_ = 8, posIterations_ = 3;
};

