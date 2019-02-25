#include "Resources.h"

const double Resources::physicsScalingFactor = 0.2;

vector<Resources::VehicleInfo> Resources::vehicles_{
	{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 50, 100, 3, 3, 3}
};

vector<Resources::SoundInfo> Resources::sounds_{
	{Default, "../Assets/sounds/default.wav"}
};

vector<Resources::KeyBindingsTnfo> Resources::keyBindings_{
	{DefaultKeys, SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDL_BUTTON_LEFT, SDLK_q, SDLK_m, SDLK_ESCAPE}
};