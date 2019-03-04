#include "Resources.h"
#include "VideoState.h"
#include "GameState.h"

Resources* Resources::singleton = nullptr;
Resources::Resources() {
	//se inicializan los estados y se almacenan en el diccionario
	introState_ = new VideoState("/YuzuGames_Intro.mp4.avi");
	//par {string, states}
	
	STATES_.insert(std::pair<string, GameState*>(NAME_INTRO_STATE, introState_));
	physicsScalingFactor = 0.2;

	vehicles_ = {
		{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 50, 100}
	};

	sounds_ = {
		{Default, "../Assets/sounds/default.wav"}
	};

}

Resources::~Resources() {
	delete introState_;
	introState_ = nullptr;
}

Resources * Resources::getInstance() {
	if (singleton == nullptr) {
		singleton = new Resources();
	}
	
	return singleton;
}

void Resources::freeResources() {

}