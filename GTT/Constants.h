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
	SDL_Keycode enterShop;
};

const struct VehicleInfo {

	string idlePath;
	string rightTurnPath;
	string leftTurnPath;
	int width;
	int height;
	float velMax; //5
	float velBackwardMax; //6 
	float turnSpeed; //7
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
	int idShoot;
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


const struct textureInfo {
	string idlePath;
	string name;
	frameAnimation frAnm;
	Vector2D pos;
	int width;
	int height;
};


//EDITABLE ----------------------------------------------------------------------------------------------------------

// PHYSICS
const enum COLLISION_GROUP {
	TILES_GROUP = -1,
	BULLETS_GROUP = -2,
};

const enum COLLISION_CATEGORY {
	TILE_CATEGORY = 0x0001,
	TAXI_CATEGORY = 0x0002,
	BULLET_CATEGORY = 0X0004,
};

//Constants Data
const float PHYSICS_SCALING_FACTOR = 0.02f;
const float DFLT_DAMPING = 1.5f;
const float DFLT_ANG_DAMPING = 12.0f;
const float HBRK_DAMPING = 0.5f;
const float DFLT_LATERAL_VELOCITY = 0.1f;
const float HBRK_LATERAL_VELOCITY = 1.0f;
const float HBRK_SPEED_DECAY = 1.2f;
const float HBRK_LATERAL_RECOVER = 0.2f;

const int TAXI_HP = 1000;
const int DMG_OVER_TIME = 5;
const int DMG_OVER_TIME_MOVING = 8;
const int DMG_FREQUENCY = 1000;

const float ENVIRONMENT_FRICTION = 0.1f;
const float DEFAULT_FRICTION = 0.2f;

//Buttons //se usa para acceder a la posici�n del array de idPath del struct ButtonInfo
const enum newGameButtonPaths {
	defaultAnm,    //la animaci�n por defecto tiene que llamarse defaultAnm para su correcta gesti�n en la clase Animation
	overButton,
	clickButton
};


//Enemy 1
const int ENEMY_HP = 100;

//NAMES
const string NAME_MAINMENU_STATE = "mainMenuState";
const string NAME_MAIN_STATE = "MainState";
const string NAME_MPEG_STATE = "MpegState";
const string NAME_GAS_MAIN_STATE = "GasMainState";
const string NAME_GAS_FILL_STATE = "GasFillState";
const string NAME_SHOP_STATE = "ShopState";



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
	//TAXI MOVEMENT
	TAXI_START,
	TAXI_IDLE,
	TAXI_ACCELERATE_01,
	TAXI_FASTDRIVE,
	TAXI_DECELERATE_10,
	TAXI_BACK_MOVING_FORWARD,
	//buttons
	CLIC_BUTTON_NEWGAME,

	//Shoots
	TURRET_DEFAULT_SOUND, //DE MOMENTO NO ESTÁ ASIGNADO A NADA, SE INICIALIZA en las torretas que no tienen asignado id
	TURRET_SHOTGUN_SHOOT,
	TURRET_SHOTGUN_SPECIAL_SHOOT,
	TURRET_GUN_SHOOT,
	TURRET_GUN_SPECIAL_SHOOT

};
const map<soundId, string> SOUND = {
	{TAXI_START, "../Assets/sounds/Arranque.wav"},
	{TAXI_IDLE, "../Assets/sounds/Idle.wav"},
	{TAXI_ACCELERATE_01, "../Assets/sounds/Taxi_Aceleration_03.wav"},
	{TAXI_FASTDRIVE, "../Assets/sounds/Taxi_fastEngineSound.wav"},
	{TAXI_DECELERATE_10, "../Assets/sounds/taxi_decel.wav"},
	{TAXI_BACK_MOVING_FORWARD, "../Assets/sounds/Taxi_frenada.wav"}, 
	{CLIC_BUTTON_NEWGAME, "../Assets/sounds/Buttons/Click_NewGameButon.wav"},
	{TURRET_SHOTGUN_SHOOT, "../Assets/sounds/Turrets/ShotGun_Normal_Shoot.wav"},
	{TURRET_SHOTGUN_SPECIAL_SHOOT, "../Assets/sounds/Turrets/ShotGun_Special_Shoot.wav"},
	{TURRET_GUN_SHOOT, "../Assets/sounds/Turrets/Gun_Normal.wav"},
	{TURRET_GUN_SPECIAL_SHOOT, "../Assets/sounds/Turrets/Gun_Special.wav"},
	{TURRET_DEFAULT_SOUND, "../Assets/sounds/Turrets/Turret_emptyBullets_Shoot.wav"}

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
const KeysScheme DEFAULT_KEYS{ SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDL_BUTTON_LEFT, SDLK_q, SDLK_m, SDLK_ESCAPE, SDLK_g };

//Fonts
const string FONT_LATO = "../Assets/fonts/lato_regular.ttf";
const string FONT_COOLFONT = "../Assets/fonts/04B_30__.ttf";

//Vehicles
const VehicleInfo TAXI{ "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 64, 32, 13.5f, 3.5f, 1.4f, 0.8f };
const VehicleInfo THECOOLERTAXI{ "../Assets/sprites/TaxiGTT.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 64, 32, 6.0f, 3.0f, 1.5f, 0.8f };
const VehicleInfo ENEMY1{ "../Assets/sprites/VTC2-cobify.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 64, 32, 13.5f, 3.5f, 1.0f, 0.8f };

//Proyectiles
	//Gun //Falta asignar ruta y sprite Y SONIDO
const ProyectileInfo GUNBULLET{ "../Assets/sprites/Turrets/Gun/Gun_Bullet.png" , 25, 25, 10, 500, 50, TURRET_GUN_SHOOT };
const ProyectileInfo SPECIAL_GUNBULLET{ "../Assets/sprites/Turrets/Gun/Special_Gun_Bullet.png" , 25, 25, 10, 500, 50, TURRET_GUN_SPECIAL_SHOOT };
	//ShotGun
const ProyectileInfo SHOTGUNBULLET{ "../Assets/sprites/Turrets/ShotGun/ShotGun_bullet.png" , 50, 50, 20, 500, 25, TURRET_SHOTGUN_SHOOT };
const ProyectileInfo SEPECIAL_SHOTGUNBULLET{ "../Assets/sprites/Turrets/ShotGun/Special_ShotGun_Bullet.png" , 25, 25, 10, 500, 50, TURRET_SHOTGUN_SPECIAL_SHOOT };
	//Snipper //Falta asignar ruta y sprite Y SONIDO
const ProyectileInfo SNIPERBULLET{};
const ProyectileInfo SPECIAL_SNIPERBULLET{};
	//MachineGun //Falta asignar ruta y sprite Y SONIDO
const ProyectileInfo MACHINEGUNBULLET{};
const ProyectileInfo SPECIAL_MACHINEGUNBULLET{};

	//... //Falta asignar ruta y sprite Y SONIDO
const ProyectileInfo BOUNCEBULLET{ "../Assets/sprites/Turrets/BlueProyectile.png", 50, 50, 10, 5000, 20, BOUNCE };



//Weapons
const WeaponInfo GUN{ "../Assets/sprites/Turrets/Gun/gun.png", "../Assets/sprites/Turrets/Gun/pistola_anim.png",2, "gun", 25, 50, 10, 300, 1500, 0.45, 0.1, 1000, GUNBULLET, SPECIAL_GUNBULLET, {LINEAR, 0, 0}, {LINEAR, 0, 0}, false, 300 };
const WeaponInfo SHOTGUN{ "../Assets/sprites/Turrets/ShotGun/shot_gun.png", "../Assets/sprites/Turrets/ShotGun/escopeta_anim.png",3, "shotgun", 20, 40, 6, 800, 4000, 0.6, 0.2, 2000, SHOTGUNBULLET, SEPECIAL_SHOTGUNBULLET, {SPREAD, 30.0, 3}, {SPREAD, 60.0, 6}, false, 100 };
//const WeaponInfo MACHINEGUN{ "../Assets/sprites/Turrets/machine_gun.png", "../Assets/sprites/Turrets/metralleta_anim.png", 2, "machinegun", 25, 50, 25, 50, 3000, 0.6, 0.2, 2000, MACHINEGUNBULLET, SPECIAL_MACHINEGUNBULLET,{LINEAR, 20.0, 30}, {LINEAR, 0, 0}, true, 500 };
//const WeaponInfo SNIPER{ "../Assets/sprites/Turrets/sniper.png", "../Assets/sprites/Turrets/francotirador_anim.png",2, "sniper", 10, 70, 4, 1000, 2000, 0.3, 0.2, 5000, SNIPERBULLET, SPECIAL_SNIPERBULLET, {LINEAR, 0, 0}, {LINEAR, 0, 0}, false, 0 };

//Maps
const string PATH_LEVEL_1 = "../Assets/maps/level1.tmx";
//const string PATH_LEVEL_1 = "../Assets/maps/test.tmx";


//Reticule
const string MAINMENURETICULE = "gun";

/**************************************/
//GAME WINDOWS
const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
const int CAMERA_WIDHT = 1920;
const int CAMERA_HEIGHT = 1080;



//MAIN MENU STATE

//atributos para gestionar propiedades de los estruct. Evitar redundancia
//background
const int backGround_widht = CAMERA_WIDHT; //se está usando el tamaño de la cam. MainMenuState.cpp
const int backGround_height = CAMERA_HEIGHT;
//Main Menu Buttons
const Vector2D NG_Button_position_ = { (CAMERA_WIDHT / 2) - 125, (CAMERA_HEIGHT - 350)};
const Vector2D EG_Button_position_ = { (CAMERA_WIDHT / 2) - 125, (CAMERA_HEIGHT - 200)};
const int Button_Width_ = 300;
const int Button_Height_ = 200;
//taxi
const Vector2D Taxi_position_ = {(CAMERA_WIDHT / 2) - 150, (CAMERA_HEIGHT / 2) - 100};
const int Taxi_Width_ = 375;
const int Taxi_Height_ = 325;
//Game title
const Vector2D title_position_ = {(CAMERA_WIDHT / 2) - 275, (CAMERA_HEIGHT / 2) - 225 };
const int title_Width_ = 700;
const int title_Height_ = 200;

//Background
const textureInfo MAIN_TITLE = { "../Assets/sprites/MainTitle/animacion_MainMenu.png", "default", {1, 1}, {0.0, 0.0}, CAMERA_WIDHT, CAMERA_HEIGHT };
//Buttons
	//siempre tienen que ser un vector, como m�nimo con un componente default animation. 
const vector <textureInfo> NEW_GAME_BUTTON = {
{"../Assets/sprites/buttons/NewGameButton/default.png", "default", {1 , 1}, NG_Button_position_, Button_Width_, Button_Height_},
{"../Assets/sprites/buttons/NewGameButton/NewGameButton_over_0.png", "overButton", {1 , 1}, NG_Button_position_, Button_Width_, Button_Height_},
{"../Assets/sprites/buttons/NewGameButton/NewGameButton_clickAnimation.png", "clickButton", {30, 1}, NG_Button_position_, Button_Width_, Button_Height_}
};

const vector <textureInfo> EXIT_BUTTON = {
{"../Assets/sprites/buttons/ExitButton/ExitButton_default.png", "default", {1 , 1}, EG_Button_position_, Button_Width_, Button_Height_},
{"../Assets/sprites/buttons/ExitButton/ExitButton_over.png", "overButton", {1 , 1}, EG_Button_position_, Button_Width_, Button_Height_}
};

//Taxi animation
const textureInfo MAIN_TITLE_TAXI = { "../Assets/sprites/MainTitle/mainTitle_taxi_default.png", "default", {1, 1}, Taxi_position_ , Taxi_Width_, Taxi_Height_ };
const textureInfo MAIN_TITLE_TAXI_ANM = { "../Assets/sprites/MainTitle/mainTitle_taxi_animation.png", "animation", {1, 1}, Taxi_position_ , Taxi_Width_, Taxi_Height_ };
//Title animation
const textureInfo MAIN_TITLE_TITLE = { "../Assets/sprites/MainTitle/MainTitle_Title_animation.png", "animation", {3, 9},  title_position_, title_Width_, title_Height_ };
/**************************************/

// GAS MENU INFO  ---------------------------
	// positions
const Vector2D FILL_GAS_BUTTON_POSITION = { (CAMERA_WIDHT / 4), (CAMERA_HEIGHT / 3) };
const Vector2D GUN_SHOP_BUTTON_POSITION = { (CAMERA_WIDHT / 2), (CAMERA_HEIGHT / 3) };
const Vector2D BACK_BUTTON_POSITION = { 3 * (CAMERA_WIDHT / 4), (CAMERA_HEIGHT / 3) };
const Vector2D PAY_BUTTON_POSITION = { 3 * (CAMERA_WIDHT / 4), 2 * (CAMERA_HEIGHT / 3) };
const Vector2D GAS_5_BUTTON_POSITION = { (CAMERA_WIDHT / 6), (CAMERA_HEIGHT / 3) };
const Vector2D GAS_10_BUTTON_POSITION = { (CAMERA_WIDHT / 3), (CAMERA_HEIGHT / 3) };
const Vector2D GAS_25_BUTTON_POSITION = { (CAMERA_WIDHT / 2), (CAMERA_HEIGHT / 3) };
const Vector2D GAS_MENU_HEALTH_BAR_POSITION = { (CAMERA_WIDHT / 6), 3 * (CAMERA_HEIGHT / 4) };
	// sizes
const int VERTICAL_BUTTON_GAS_W = 275;
const int VERTICAL_BUTTON_GAS_H = 570;
const int HORIZONTAL_BUTTON_GAS_W = 350;
const int HORIZONTAL_BUTTON_GAS_H = 200;
const int SQUARE_BUTTON_GAS_W = 275;
const int SQUARE_BUTTON_GAS_H = 200;
const int GAS_BACKGROUND_W = CAMERA_WIDHT;
const int GAS_BACKGROUND_H = CAMERA_HEIGHT;
	// paths
const textureInfo GAS_BACKGROUND_INFO = { "../Assets/sprites/GasMenu/background-gasolinera.png", "default", {1, 1}, {0.0, 0.0}, GAS_BACKGROUND_W, GAS_BACKGROUND_H };
const textureInfo FILL_GAS_BUTTON_INFO = { "../Assets/sprites/GasMenu/button-fill-gas.png", "default", {1, 1}, FILL_GAS_BUTTON_POSITION, VERTICAL_BUTTON_GAS_W, VERTICAL_BUTTON_GAS_H };
const textureInfo GUN_SHOP_BUTTON_INFO = { "../Assets/sprites/GasMenu/button-gun-shop.png", "default", {1, 1}, GUN_SHOP_BUTTON_POSITION, VERTICAL_BUTTON_GAS_W, VERTICAL_BUTTON_GAS_H };
const textureInfo BACK_BUTTON_INFO = { "../Assets/sprites/GasMenu/button-back.png", "default", {1, 1}, BACK_BUTTON_POSITION, HORIZONTAL_BUTTON_GAS_W, HORIZONTAL_BUTTON_GAS_H };
const textureInfo PAY_BUTTON_INFO = { "../Assets/sprites/GasMenu/button-pay.png", "default", {1, 1}, PAY_BUTTON_POSITION, HORIZONTAL_BUTTON_GAS_W, HORIZONTAL_BUTTON_GAS_H };
const textureInfo GAS_5_BUTTON_INFO = { "../Assets/sprites/GasMenu/button-5.png", "default", {1, 1}, GAS_5_BUTTON_POSITION, SQUARE_BUTTON_GAS_W, SQUARE_BUTTON_GAS_H };
const textureInfo GAS_10_BUTTON_INFO = { "../Assets/sprites/GasMenu/button-10.png", "default", {1, 1}, GAS_10_BUTTON_POSITION, SQUARE_BUTTON_GAS_W, SQUARE_BUTTON_GAS_H };
const textureInfo GAS_25_BUTTON_INFO = { "../Assets/sprites/GasMenu/button-25.png", "default", {1, 1}, GAS_25_BUTTON_POSITION, SQUARE_BUTTON_GAS_W, SQUARE_BUTTON_GAS_H };
// --------------------------------------------


//TAXI SOUND MANAGER
const int VOL_CHANNEL_2 = 90; //regular engine
const int VOL_CHANNEL_3 = 40; //aceleration
const int VOL_CHANNEL_6 = 60; //BackForward
const double POR_VEL_MIN_ = 0.15;
const double POR_VEL_MIN_2_ = 0.2;
const double POR_VEL_MIN_3_ = 0.9;

#endif // !constants_define