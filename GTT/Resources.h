#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include <Box2D/Box2D.h>

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


	static vector <VehicleInfo> vehicles_;
	static vector<SoundInfo> sounds_;
	static vector <KeyBindingsInfo> keyBindings_;

	static const float physicsScalingFactor;

	// Taxi movement variables
	static const float defaultDamping;
	static const float handbrakeDamping;
	static const float defaultLateralVelocity;
	static const float handbrakeLateralVelocity;
	static const float handbrakeSpeedDecay;
};

