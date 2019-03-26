#include "Resources.h"

// States
#include "MainMenuState.h"
#include "MainState.h"


Resources* Resources::singleton_ = nullptr;

Resources::Resources() {
	physicsScalingFactor = 0.02f;
	handbrakeDamping = 0.7f;
	defaultLateralVelocity = 0;
	handbrakeLateralVelocity = 0.9999f;
	handbrakeSpeedDecay = 0.0004f;

	defaultDamping = 1.3f;

	vehicles_ = {
		{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 200, 100, 13.5, 3.5, 1, 0.5f}
	};

	sounds_ = {
		{Default_Sound, "../Assets/sounds/default.wav"}
	};

	music_ = {
		{Default_Music, "../Assets/sounds/default.wav"}
	};

	fonts_ = {
		{Default_Font, "../Assets/fonts/lato_regular.ttf"}
	};

	keyBindings_ = {
		{DefaultKeys, SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDL_BUTTON_LEFT, SDLK_q, SDLK_m, SDLK_ESCAPE}
	};
}



Resources::~Resources() {
	//delete introState_;
	//introState_ = nullptr;
}

Resources * Resources::getInstance() {
	if (singleton_ == nullptr) {
		singleton_ = new Resources();
	}

	return singleton_;
}

void Resources::initStates() {
	// Main menu
	STATES_.insert(std::pair<string, GameState*>(NAME_MAINMENU_STATE, new MainMenuState()));

	// Main game
	STATES_.insert(std::pair<string, GameState*>(NAME_MAIN_STATE, new MainState()));
}
