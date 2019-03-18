#pragma once
#include <Box2D/Box2D.h>

using namespace std;

// ----------------- S I Z E S ---------------------
const unsigned int WIN_WIDTH = 1280;
const unsigned int WIN_HEIGHT = 720;

const int CAMERA_WIDTH = 1600;
const int CAMERA_HEIGHT = 900;


// ------------- P L A C E M E N T ----------------
const double BUTTON_X_POSITION = 500.0;
const double BUTTON_Y_POSITIONS[2] = { 150.0, 500.0 };


// ----------------- W O R L D ---------------------
const b2Vec2 GRAVITY(0, 10);


// ----------- T E X T U R E  P A T H S ------------
const string PATH_AIR_STRIKE = "../Assets/sprites/air_strike.png";
const string PATH_AIR_STRIKE_X = "../Assets/sprites/air_strike.png";
const string PATH_BULLET = "../Assets/sprites/bullet.png";
const string PATH_BUTTONS[] = { "../Assets/sprites/button-play.png",
								"../Assets/sprites/button-exit.png"};
const string PATH_DEFAULT_TEXTURE = "../Assets/sprites/default.png";
const string PATH_ESCOPETA_ANIM = "../Assets/sprites/escopeta_anim.png";
const string PATH_FLAME_THROWER = "../Assets/sprites/flame_thrower.png";
const string PATH_GUN = "../Assets/sprites/gun.png";
const string PATH_GUN_ANIM = "../Assets/sprites/pistola_anim.png";
const string PATH_RETICULE = "../Assets/sprites/gunreticule.png";
const string PATH_HEALTH_BACKGROUND = "../Assets/sprites/health_background.png";
const string PATH_HEALTH_BAR = "../Assets/sprites/health_bar.png";
const string PATH_MACHINE_GUN = "../Assets/sprites/machine_gun.png";
const string PATH_PROJECTILE = "../Assets/sprites/projectile.png";
const string PATH_SHOT_GUN = "../Assets/sprites/shot_gun.png";
const string PATH_SNIPER = "../Assets/sprites/sniper.png";
const string PATH_TAXI = "../Assets/sprites/taxi.png";
const string PATH_VTC2 = "../Assets/sprites/VTC2-cobify.png";


// -------------- S O U N D  P A T H S -------------
const string PATH_DEFAULT_SOUND = "../Assets/sounds/default.wav";