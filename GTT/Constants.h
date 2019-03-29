#pragma once
#include <SDL.h>

#ifndef constants_define
#define constants_define

using namespace std;

//DO NOT EDIT ---------------------------------------------------------------------------------------------------------------
enum ProyectileType {
	GUNB,
	SHOTGUNB,
};
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

const struct WeaponInfo {
	string idlePath;
	string shootPath;
	string reticuleSprite;
	int width;
	int height;
	int maxAmmo;
	int cadence;
	int reloadTime;
	double perfRelIni;
	double perfRelSeg;
	int chargeTime;
	ProyectileType normalB;
	ProyectileType specialB;
	bool automatic;
	double prop1;
	int prop2;

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
const int DMG_OVER_TIME_MOVING = 8;
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

//Weapons
const WeaponInfo GUN{ "../Assets/sprites/gun.png", "../Assets/sprites/pistola_anim.png", "gun", 75, 150, 10, 150, 1500, 0.45, 0.1, 1000, GUNB, SHOTGUNB, false};
const WeaponInfo SHOTGUN{ "../Assets/sprites/shot_gun.png", "../Assets/sprites/escopeta_anim.png", "shotgun", 75, 150, 6, 900, 4000, 0.6, 0.2, 2000, SHOTGUNB, GUNB, false, 30.0, 3};
const WeaponInfo MACHINEGUN{ "../Assets/sprites/machine_gun.png", "../Assets/sprites/machine_gun.png", "machinegun", 75, 150, 25, 50, 3000, 0.6, 0.2, 2000, GUNB, SHOTGUNB, true};
const WeaponInfo SNIPER{"../Assets/sprites/sniper.png", "../Assets/sprites/sniper.png", "sniper", 75, 150, 4, 1000, 2000, 0.3, 0.2, 5000, GUNB, SHOTGUNB, false };


#endif // !constants_define
