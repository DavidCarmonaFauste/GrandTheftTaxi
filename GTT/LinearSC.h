#pragma once
#include "ShootComponent.h"

//Componente de disparo para armas que disparan balas de una en una con 
//una trayectoria lineal

class LinearSC : public ShootComponent
{
public:
	LinearSC(ProyectilePool* bPool, Turret* turret) :ShootComponent(bPool, turret) {};
	virtual void shoot();
	virtual ~LinearSC() {};
};

