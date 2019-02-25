#pragma once
#include <string>
#include <vector>
using namespace std;

class Resources
{

public:
	enum SoundId {
		DefaultSoundId
	};

	enum MusicId {
		DefaultMusicId
	};

	enum VehicleId {
		// TAXI
		Taxi
	};

	struct SoundInfo {
		SoundId id;
		string path;
	};

	struct MusicInfo{
		MusicId id;
		string path;
	};

	struct VehicleInfo {
		VehicleId id;
		string idlePath;
		string rightTurnPath;
		string leftTurnPath;
		int width;
		int height;
	};


	static vector <VehicleInfo> vehicles_;
	static vector <SoundInfo> sounds_;
	static vector <MusicInfo> music_;

	static const double physicsScalingFactor;
};

