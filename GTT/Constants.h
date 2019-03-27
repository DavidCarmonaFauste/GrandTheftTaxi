#pragma once
#include <SDL.h>

#ifndef constants_define
#define constants_define

using namespace std;

//DO NOT EDIT ---------------------------------------------------------------------------------------------------------------
const struct KeysScheme {
	SDL_Keycode forward;
	SDL_Keycode backwards;
	SDL_Keycode turnRight;
	SDL_Keycode turnLeft;
	SDL_Keycode mainAction;
	SDL_MouseButtonEvent swapWeapon;
	SDL_Keycode openMap;
	SDL_Keycode mainMenu;
};

const struct VehicleInfo{

	string idlePath;
	string rightTurnPath;
	string leftTurnPath;
	int width;
	int height;
	float velMax;
	float velBackwardMax;
	float turnSpeed;
	float acceleration;
};

//EDITABLE ----------------------------------------------------------------------------------------------------------

//Constants Data
const float PHYSICS_SCALING_FACTOR = 0.02f;
const float DFLT_DAMPING = 1.5f;
const float DFLT_ANG_DAMPING = 1.5f;
const float HBRK_DAMPING = 0.7f;
const float DFLT_LATERAL_VELOCITY = 0.1f;
const float HBRK_LATERAL_VELOCITY = 1.01f;
const float HBRK_SPEED_DECAY = 0.0004f;

const int TAXI_HP = 1000;
const int DMG_OVER_TIME = 5;
const int DMG_OVER_TIME_MOVING = 10;
const int DMG_FREQUENCY = 1000;

//States
const string NAME_MAINMENU_STATE = "mainMenuState";
const string NAME_MAIN_STATE = "MAIN_STATE";

//SOUNDS
const enum soundId {
	DEFAULT_SOUND,
};
const map<soundId, string> SOUND = {
	{DEFAULT_SOUND, "../Assets/sounds/default.wav"}
};

//MUSIC
const enum musicId {
	DEFAULT_MUSIC,
};

const map<musicId, string> MUSIC = {
	{DEFAULT_MUSIC, "../Assets/sounds/default.wav"}
};


//KeyBindings
const KeysScheme DEFAULT_KEYS{ SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDL_BUTTON_LEFT, SDLK_q, SDLK_m, SDLK_ESCAPE };

//Fonts
const string FONT_LATO = "../Assets/fonts/lato_regular.ttf";

//Vehicles
const VehicleInfo TAXI { "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 200, 100, 13.5f, 3.5f, 1.4f, 0.8f };

#endif // !constants_define
