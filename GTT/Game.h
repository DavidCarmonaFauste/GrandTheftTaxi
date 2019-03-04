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

private:
	bool exit_ = false;

	//provisional
	//se instancia en clase Game.h y se gestiona render, update y handleEvent de los estados en pila 
	GameStateMachine* gmStMachine_;
	VideoState* videoIntro_;
	//*SDL_Event event; //PROVISIONAL, DEBE CAMBIRSE POR COMPONENTE FÍSICAS

	static Game* singleton;
	Game();
	virtual ~Game();
};

