#include "Resources.h"

const float Resources::physicsScalingFactor = 0.2f;

vector<Resources::VehicleInfo> Resources::vehicles_{
	{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 100, 50, 120.0f, 30.0f, 3.0f, 0.8f}
};

vector<Resources::SoundInfo> Resources::sounds_{
	{Default, "../Assets/sounds/default.wav"}
};

vector<Resources::KeyBindingsInfo> Resources::keyBindings_{
	{DefaultKeys, SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDL_BUTTON_LEFT, SDLK_q, SDLK_m, SDLK_ESCAPE}
};