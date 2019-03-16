#pragma once
#include "ShootComponent.h"

//Componente de disparo para armas que disparan multiples perdigones 
//en cada disparo con cierto grado de dispersion

class SpreadSC : public ShootComponent
{
public:
	SpreadSC(Turret* turret, double dispersionAngle, int pellets);
	virtual void shoot();
	virtual ~SpreadSC() {};
protected:
	double dispersionAngle_;
	int numPellets_;//numero de perdigones > 1
};

