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
	SDL_Keycode swapWeapon;
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

const enum ImpactMode {
	STANDARD,
	BOUNCE,
	EXPLOSIVE
};
const struct ProyectileInfo {
	string idlePath;
	int width;
	int height;
	double damage;
	double lifeTime;
	double speed;
	ImpactMode imp = STANDARD;
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
	int chargedShotDelay;
};

const struct frameAnimation {
	int cols;
	int rows;
};

const struct ButtonInfo {
	string idlePath; 
	string name; 
	frameAnimation frAnm;
	Vector2D pos;
};

const struct mainTitleInfo {
	string idlePath;
	string name;
	frameAnimation frAnm;
	Vector2D pos;
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

const float FUEL_VALUE = 0.15f;

//Buttons //se usa para acceder a la posici�n del array de idPath del struct ButtonInfo
const enum newGameButtonPaths {
	defaultAnm,    //la animaci�n por defecto tiene que llamarse defaultAnm para su correcta gesti�n en la clase Animation
	overButton,
	clickButton
};

//MainTitle
const enum mainTitlePaths {
	title_defaultAnm,
	texAnm,
};

//Enemy 1
const int ENEMY_HP = 500;

//NAMES
const string NAME_MAINMENU_STATE = "mainMenuState";
const string NAME_MAIN_STATE = "MAIN_STATE";
const string NAME_SHOP_STATE = "SHOP_STATE";
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
	TAXI_DECELERATE_10,
	//buttons
	CLIC_BUTTON_NEWGAME
};
const map<soundId, string> SOUND = {
	{DEFAULT_SOUND, "../Assets/sounds/default.wav"},
	{TAXI_START, "../Assets/sounds/Arranque.wav"},
	{TAXI_IDLE, "../Assets/sounds/Idle.wav"},
	{TAXI_ACCELERATE_01, "../Assets/sounds/Accelerate01.wav"},
	{TAXI_1, "../Assets/sounds/Running1.wav"},
	{TAXI_DECELERATE_10, "../Assets/sounds/Desacel10.wav"},
	{CLIC_BUTTON_NEWGAME, "../Assets/sounds/Buttons/Click_NewGameButon.wav"}
};


//MUSIC
const enum musicId {
	DEFAULT_MUSIC,
	MAIN_THEME_MUSIC
};

const map<musicId, string> MUSIC = {
	{DEFAULT_MUSIC, "../Assets/sounds/default.wav"},
	{MAIN_THEME_MUSIC, "../Assets/sounds/MainTheme/Grove.wav"}
};


//KeyBindings
const KeysScheme DEFAULT_KEYS{ SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_q, SDL_BUTTON_LEFT, SDLK_m, SDLK_ESCAPE };

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
const ProyectileInfo BOUNCEBULLET{ "../Assets/sprites/BlueProyectile.png", 50, 50, 10, 5000, 20, BOUNCE};

//Weapons
const WeaponInfo GUN{ "../Assets/sprites/gun.png", "../Assets/sprites/pistola_anim.png",2, "gun", 75, 150, 10, 300, 1500, 0.45, 0.1, 1000, GUNBULLET, SHOTGUNBULLET, {LINEAR, 0, 0}, {LINEAR, 0, 0}, false, 300};
const WeaponInfo SHOTGUN{ "../Assets/sprites/shot_gun.png", "../Assets/sprites/escopeta_anim.png",3, "shotgun", 50, 100, 6, 800, 4000, 0.6, 0.2, 2000, SHOTGUNBULLET, GUNBULLET, {SPREAD, 30.0, 3}, {SPREAD, 60.0, 6}, false, 100};
const WeaponInfo MACHINEGUN{ "../Assets/sprites/machine_gun.png", "../Assets/sprites/metralleta_anim.png", 2, "machinegun", 75, 150, 25, 50, 3000, 0.6, 0.2, 2000, GUNBULLET, BOUNCEBULLET,{LINEAR, 20.0, 30}, {LINEAR, 0, 0}, true, 500};
const WeaponInfo SNIPER{"../Assets/sprites/sniper.png", "../Assets/sprites/francotirador_anim.png",2, "sniper", 25, 150, 4, 1000, 2000, 0.3, 0.2, 5000, SNIPERBULLET, SHOTGUNBULLET, {LINEAR, 0, 0}, {LINEAR, 0, 0}, false, 0};



//Buttons
//siempre tienen que ser un vector, como m�nimo con un componente default animation. 
const vector <ButtonInfo> NEW_GAME_BUTTON = { {"../Assets/sprites/buttons/NewGameButton/default.png", "default", {1 , 1}, {550.0, 660.0}}, 
{"../Assets/sprites/buttons/NewGameButton/NewGameButton_over_0.png", "overButton", {1 , 1}, {550.0, 660.0}},
{"../Assets/sprites/buttons/NewGameButton/NewGameButton_clickAnimation.png", "clickButton", {30, 1}, {550.0, 660.0}}
};

const vector <ButtonInfo> EXIT_BUTTON = { {"../Assets/sprites/buttons/ExitButton/ExitButton_default.png", "default", {1 , 1}, {1000.0, 700.0}},
{"../Assets/sprites/buttons/ExitButton/ExitButton_over.png", "overButton", {1 , 1}, {1000.0, 700.0}} };

const string MAINMENURETICULE = "gun";

const vector<mainTitleInfo>MAIN_TITLE = { {"../Assets/sprites/MainTitle/default.png", "default", {1, 1}, {0.0, 0.0} }, 
{"../Assets/sprites/MainTitle/animacion_MainMenu.png", "animation", {5,8}, {0.0, 0.0} }, 
};







#endif // !constants_define

