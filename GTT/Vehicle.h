#pragma once

using namespace std;

class Turret;

class Vehicle //: public GameObject
{
public:
	Vehicle();
	virtual ~Vehicle();

	void Destroy();

protected:
	float maxSpeed_;
	float maxRotationSpeed_;

	Turret* primaryWeapon_, *secondaryWeapon_;
	bool enemy_;
	int health_;
};
