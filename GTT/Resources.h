#pragma once
#include <string>
#include <vector>
#include <map>
#include "GameState.h"


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

	enum MusicId {
		Default_Music
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

	struct MusicInfo {
		MusicId id;
		string path;
	};

	static Resources* getInstance();
	void initStates();

	vector <VehicleInfo> vehicles_;
	vector <SoundInfo> sounds_;
	vector <MusicInfo> music_;

	double physicsScalingFactor;

	map <string, GameState*> STATES_;

private:

	// Singleton instance
	static Resources *singleton_;

	Resources();
	virtual ~Resources();
};
