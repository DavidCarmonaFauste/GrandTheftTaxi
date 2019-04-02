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

const struct ProyectileInfo {
	string idlePath;
	int width;
	int height;
	double damage;
	double lifeTime;
	double speed;
};

const enum FireMode {
	LINEAR,
	SPREAD
};
struct ShootMode {
	FireMode firemode;
	double prop1;
	int prop2;
};
const struct WeaponInfo {
	string idlePath;
	string shootPath;
	int animationFrames;
	string reticuleSprite;
	int width;
	int height;
	int maxAmmo;
	int cadence;
	int reloadTime;
	double perfRelIni;
	double perfRelSeg;
	int chargeTime;
	ProyectileInfo normalB;
	ProyectileInfo specialB;
	ShootMode shootMode1;
	ShootMode shootMode2;
	bool automatic;
};

enum ButtonTypes { MainMenuPlay, MainMenuExit }; 


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

const double BUTTON_X_POSITION = 500.0;
const double BUTTON_Y_POSITIONS[2] = { 150.0, 500.0 };

//Enemy 1
const int ENEMY_HP = 500;

//States
const string NAME_MAINMENU_STATE = "mainMenuState";
const string NAME_MAIN_STATE = "MainState";
const string NAME_MPEG_STATE = "MpegState";

//VIDEOS
const enum videoId {
	INTRO_VIDEO
};
const map <videoId, string> VIDEOS = {
	{INTRO_VIDEO, "../Assets/videos/YuzuGames_Intro.mpg"}
};
const map <videoId, string> VIDEO_NEXTSTATE = {
	{INTRO_VIDEO, NAME_MAINMENU_STATE}
};

//SOUNDS
const enum soundId {
	DEFAULT_SOUND,
	TAXI_START,	//TAXI MOVEMENT
	TAXI_IDLE,
	TAXI_ACCELERATE_01,
	TAXI_1,
	TAXI_DECELERATE_10
};
const map<soundId, string> SOUND = {
	{DEFAULT_SOUND, "../Assets/sounds/default.wav"},
	{TAXI_START, "../Assets/sounds/Arranque.wav"},
	{TAXI_IDLE, "../Assets/sounds/Idle.wav"},
	{TAXI_ACCELERATE_01, "../Assets/sounds/Accelerate01.wav"},
	{TAXI_1, "../Assets/sounds/Running1.wav"},
	{TAXI_DECELERATE_10, "../Assets/sounds/Desacel10.wav"}

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
const string FONT_COOLFONT = "../Assets/fonts/04B_30__.ttf";

//Vehicles
const VehicleInfo TAXI { "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 200, 100, 13.5f, 3.5f, 1.4f, 0.8f };
const VehicleInfo THECOOLERTAXI{ "../Assets/sprites/TaxiGTT.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 200, 100, 13.5f, 5.0f, 1.0f, 0.8f };
const VehicleInfo ENEMY1{ "../Assets/sprites/VTC2-cobify.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 200, 100, 13.5f, 3.5f, 1.0f, 0.8f };

//Proyectiles
const ProyectileInfo GUNBULLET{ "../Assets/sprites/BlueProyectile.png" , 25, 25, 10, 500, 50 };
const ProyectileInfo SHOTGUNBULLET{ "../Assets/sprites/bullet.png" , 50, 50, 20, 500, 25 };
const ProyectileInfo SNIPERBULLET{ "../Assets/sprites/bullet.png", 40, 40, 10, 500, 100};
const ProyectileInfo MACHINEGUNBULLET{};

//Weapons
const WeaponInfo GUN{ "../Assets/sprites/gun.png", "../Assets/sprites/pistola_anim.png",2, "gun", 75, 150, 10, 150, 1500, 0.45, 0.1, 1000, GUNBULLET, SHOTGUNBULLET, {LINEAR, 1, 1}, {LINEAR, 1, 1}, false };
const WeaponInfo SHOTGUN{ "../Assets/sprites/shot_gun.png", "../Assets/sprites/escopeta_anim.png",3, "shotgun", 50, 100, 6, 900, 4000, 0.6, 0.2, 2000, SHOTGUNBULLET, GUNBULLET, {SPREAD, 30.0, 3}, {SPREAD, 60.0, 6}, false };
const WeaponInfo MACHINEGUN{ "../Assets/sprites/machine_gun.png", "../Assets/sprites/metralleta_anim.png", 2, "machinegun", 75, 150, 25, 50, 3000, 0.6, 0.2, 2000, GUNBULLET, SHOTGUNBULLET,{LINEAR, 1, 1}, {LINEAR, 1, 1}, true};
const WeaponInfo SNIPER{"../Assets/sprites/sniper.png", "../Assets/sprites/francotirador_anim.png",2, "sniper", 25, 150, 4, 1000, 2000, 0.3, 0.2, 5000, SNIPERBULLET, SHOTGUNBULLET, {LINEAR, 1, 1}, {LINEAR, 1, 1}, false };

//Buttons  ---- to be used along with the ButtonType enum to pick texture
const string PATH_BUTTONS[] = { "../Assets/sprites/button-play.png",
								"../Assets/sprites/button-exit.png"};




#endif // !constants_define
