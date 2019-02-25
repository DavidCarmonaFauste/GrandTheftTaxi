#pragma once
#include <string>
#include <vector>
#include <SDL.h>
using namespace std;

class Resources
{

public:
	enum SoundId {
		Default
	};

	enum KeyBindingsId {
		DefaultKeys
	};

	enum VehicleId
	{
		//TAXI
		Taxi
	};

	struct KeyBindingsTnfo {
		SDL_Keycode forward;
		SDL_Keycode backwards;
		SDL_Keycode turnRight;
		SDL_Keycode turnLeft;
		SDL_Keycode mainAction;
		SDL_MouseButtonEvent swapWeapon;
		SDL_Keycode openMap;
		SDL_Keycode mainMenu;
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
		double velMax;
		double velBackwardMax;
		double turnSpeed;
	};


	static vector <VehicleInfo> vehicles_;
	static vector<SoundInfo> sounds_;
	static vector <KeyBindingsTnfo> keyBindings_;

	static const double physicsScalingFactor;
};

