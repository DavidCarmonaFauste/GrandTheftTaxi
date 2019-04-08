#pragma once
#include "Container.h"
#include "Animation.h"
#include "PhysicObject.h"
#include "Trigger.h"

enum proyectileType {
	BULLET,
	FLAME,
	STRIKE
};

class Proyectile : public Trigger {
public:
	Proyectile();
	virtual void Impact();
	virtual void SetBirth(double birthTime);
	virtual void update(Uint32 time);
	virtual void ChangeBulletType(ProyectileInfo p);
	PhysicObject* GetPhyO();
	double GetSpeed();
	virtual void beginCallback(b2Contact * contact);
	virtual void endCallback(b2Contact * contact);
	virtual ~Proyectile() {};

protected:
	Animation* animC_;
	PhysicObject* phyO_;
	double damage_;
	double lifeTime_;//tiempo de vida hasta volver a desactivarse
	double birthTime_;//tiempo en el que se activo el objeto
	double speed_;
};

