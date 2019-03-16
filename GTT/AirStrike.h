#pragma once
#include "Turret.h"

class AirStrike : public Turret
{
public:
	AirStrike();
	virtual void Shoot();
	virtual ~AirStrike() {};
protected:
	//double waitingShotTime_ = 1;
	//double shooting_; //indica si se está disparando (para AirStrike)

};

