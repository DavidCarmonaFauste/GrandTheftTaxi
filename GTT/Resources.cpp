#include "Resources.h"

const double Resources::physicsScalingFactor = 0.2;

vector<Resources::VehicleInfo> Resources::vehicles_{
	{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 50, 100}
};

vector<Resources::SoundInfo> Resources::sounds_{
	{Default, "../Assets/sounds/default.wav"}
};

vector<string> Resources::estados_{
	{"IntroState_", "MainMenu_State_","GameState_","PauseMenuState_"}
};

