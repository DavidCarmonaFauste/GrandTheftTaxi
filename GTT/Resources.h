#pragma once
#include <string>
#include <vector>
using namespace std;

class Resources
{

public:
	enum VehicleId
	{
		//TAXI
		Taxi
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

};

