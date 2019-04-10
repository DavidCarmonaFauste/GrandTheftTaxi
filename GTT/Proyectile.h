#pragma once
#include "Container.h"
#include "Animation.h"
#include "PhysicObject.h"
#include "Trigger.h"


class Proyectile : public Trigger {
public:
	Proyectile();
	virtual void Impact();
	virtual void SetBirth(double birthTime);
	virtual void update(Uint32 time);
	virtual void ChangeBulletType(ProyectileInfo p);
	virtual void beginCallback(b2Contact *contact) override;
	virtual void endCallback(b2Contact *contact) override;
	PhysicObject* GetPhyO();
	double GetSpeed();
	virtual ~Proyectile() {};

protected:
	Animation* animC_;
	double damage_;
	double lifeTime_;//tiempo de vida hasta volver a desactivarse
	double birthTime_;//tiempo en el que se activo el objeto
	double speed_;
};

