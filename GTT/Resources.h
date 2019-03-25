#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include <Box2D/Box2D.h>
#include <map>
#include "GameState.h"
#include "Font.h"

using namespace std;


//static const string NAME_INTRO_STATE = "introState";
static const string NAME_MAINMENU_STATE = "mainMenuState";
static const string NAME_MAIN_STATE = "MAIN_STATE";

class Resources
{
public:
	enum SoundId {
		Default_Sound
	};
	
	enum KeyBindingsId {
		DefaultKeys
	};
	
	enum MusicId {
		Default_Music
	};

	enum VehicleId {
		//TAXI
		Taxi
	};

	struct KeyBindingsInfo {
		KeyBindingsId id;
		SDL_Keycode forward;
		SDL_Keycode backwards;
		SDL_Keycode turnRight;
		SDL_Keycode turnLeft;
		SDL_Keycode mainAction;
		SDL_MouseButtonEvent swapWeapon;
		SDL_Keycode openMap;
		SDL_Keycode mainMenu;
	};
	
	enum FontId {
		Default_Font
	};

	struct SoundInfo
	{
		SoundId id;
		string path;
	};

	struct VehicleInfo
	{
		VehicleId id;
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

	struct MusicInfo {
		MusicId id;
		string path;
	};
	
	static Resources* getInstance();
	void initStates();

	vector <VehicleInfo> vehicles_;
	vector <SoundInfo> sounds_;
	vector <MusicInfo> music_;
	vector <KeyBindingsInfo> keyBindings_;
	map<FontId, string> fonts_;

	double physicsScalingFactor;

	map <string, GameState*> STATES_;

	// Taxi movement variables
	float defaultDamping;
	float handbrakeDamping;
	float defaultLateralVelocity;
	float handbrakeLateralVelocity;
	float handbrakeSpeedDecay;

private:
	// Singleton instance
	static Resources *singleton_;

	Resources();
	virtual ~Resources();
};
