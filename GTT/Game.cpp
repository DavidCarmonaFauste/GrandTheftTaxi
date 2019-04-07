#include "Game.h"
#include <iostream>

using namespace std;

Game* Game::singleton_ = nullptr;

Game::Game() {
	// Initialization values
	int winX_, winY_;
	winX_ = winY_ = SDL_WINDOWPOS_CENTERED;

	// SDL initialization
	SDL_Init(SDL_INIT_EVERYTHING);
	
	// SDL_Mixer initialization
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		cout << "SDL Mixer initialization failed";

	// SDL_TTF initialization
	TTF_Init();

	window_ = SDL_CreateWindow("Grand Theft Taxi", winX_, winY_,
		winWidth_, winHeight_, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer_, cameraWidth, cameraHeight);
	//SDL_SetRelativeMouseMode(SDL_TRUE); //This line makes mouse movement in the menu state impossible

	world_ = new b2World(b2Vec2(0, 0));
	soundManager_ = new SoundManager();

	// Check for errors
	if (window_ == nullptr || renderer_ == nullptr) {
		cout << "SDL initialization failed\n";
	}
	SDL_ShowCursor(0);
}

Game::~Game() {

}

//los eventos los gestiona la aplicaci�n. Conecta directamente con handleEvents del estado actual. 
void Game::handleEvents(Uint32 deltaTime) {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit_) {
		// Call the handleEvents of the cameras and the state
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				exit_ = true;
			}
			
			else if (event.key.keysym.sym == SDLK_f) {
				SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
			}
		}
		for (auto cam : cameras_) cam.second->handleInput(deltaTime, event);
		gmStMachine_->get_CurrentState()->handleEvents(deltaTime, event);
		if (event.type == SDL_QUIT) exit_ = true; //exit_ comunica con main a trav�s del m�todo exitGame
	}
}
void Game::update(Uint32 deltaTime)
{
	accumulator_ += deltaTime;
	while (accumulator_ >= step_*1000) {
		world_->Step(step_, velIterations_, posIterations_);
		accumulator_ -= step_*1000;
	}

	// Update the cameras and the state
	gmStMachine_->get_CurrentState()->update(deltaTime);
	for (auto cam : cameras_) cam.second->update(deltaTime);
}
void Game::render(Uint32 deltaTime)
{
	SDL_RenderClear(renderer_);

	// Render the cameras and the state
	for (auto cam : cameras_) cam.second->render(deltaTime);
	gmStMachine_->get_CurrentState()->render(deltaTime);

	SDL_RenderPresent(renderer_);
}

SDL_Renderer * Game::getRenderer()
{
	return renderer_;
}

SDL_Window * Game::getWindow()
{
	return window_;
}

int Game::getWindowWidth()
{
	return winWidth_;
}

int Game::getWindowHeight()
{
	return winHeight_;
}

int Game::getCameraHeight()
{
	return cameraHeight;
}

int Game::getCameraWidth()
{
	return cameraWidth;
}

b2World * Game::getWorld()
{
	return world_;
}

SoundManager * Game::getSoundManager()
{
	return soundManager_;
}

Camera * Game::getCamera(cameraType cT)
{
	return cameras_[cT];
}

void Game::setState(string state){
	gmStMachine_->setState(state);
}

void Game::init() {
	cameras_[GAME_CAMERA] = new Camera(1600, 900);
	cameras_[UI_CAMERA] = new Camera(1600, 900);

	// Create the resources singleton for the first time
	// and initialize its states
	gmStMachine_ = new GameStateMachine();
	gmStMachine_->initStates();
}

Game * Game::getInstance() {
	if (singleton_ == nullptr)
		singleton_ = new Game();

	return singleton_;
}

//Run es llamado desde Main y gestiona los update, render y hangleEvents de los estados
void Game::run() {
	init();

	double lastTime = SDL_GetTicks();
	double deltaTime = lastTime;

	while (!exit_) {
		handleEvents(deltaTime);
		update(deltaTime);
		render(deltaTime);

		// Update the delta time
		deltaTime = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

//exitGame devuelve el valor del atributo, determina la ruptura del bucle en Main.cpp
bool Game::exitGame() {
	return exit_;
}


