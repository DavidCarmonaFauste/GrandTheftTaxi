#pragma once
#include <string>
#include <vector>
#include <map>
#include "GameState.h"
using namespace std;

class VideoState;
class GameState;


static const string NAME_INTRO_STATE = "introState";
//static const string NAME_INTRO_STATE = "introState";
//static const string NAME_INTRO_STATE = "introState";
//static const string NAME_INTRO_STATE = "introState";
class Resources
{
public:
	enum SoundId {
		Default
	};

	enum VehicleId {
		//TAXI
		Taxi
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
	};

	static Resources* getInstance();
	
	vector <VehicleInfo> vehicles_;
	vector <SoundInfo> sounds_;
	double physicsScalingFactor;

	map <string, GameState*> STATES_;
	
private:
	Resources();
	~Resources();

	// Singleton instance
	static Resources *singleton;

	void freeResources();

	VideoState *introState_ = nullptr;
};
