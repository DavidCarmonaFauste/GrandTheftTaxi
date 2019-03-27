#pragma once
#include "ShootComponent.h"

//Componente de disparo para armas que disparan balas de una en una con 
//una trayectoria lineal

class LinearSC : public ShootComponent
{
public:
	LinearSC(Turret* turret) :ShootComponent(turret) {};
	virtual void shoot(ProyectileType prType);
	virtual void changeProperties(double prop1, int prop2) {};
	virtual ~LinearSC() {};
};

