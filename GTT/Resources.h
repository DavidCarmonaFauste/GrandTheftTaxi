#pragma once
#include <string>
#include <vector>
using namespace std;

class Resources
{

public:
	enum SoundId {
		Default
	};

	enum VehicleId
	{
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


	static vector <VehicleInfo> vehicles_;
	static vector <SoundInfo> sounds_;

	static const bool physicsScalingFactor = 0.05;
};

