#pragma once
#include "Container.h"
#include"FollowGameObject.h"
#include "Vehicle.h"
#include "ProyectilePool.h"

class Animation;
class ShootComponent;
class Reticule;


//clase abstracta, padre de los diferentes tipos de torreta
class Turret : public Container
{
public:
	Turret();
	virtual void render(Uint32 deltaTime);
	virtual void update(Uint32 deltaTime);
	virtual void AttachToVehicle(Vehicle* car);
	proyectileType GetProyectileType();
	virtual void Shoot();
	virtual void Reload();
	virtual int GetSpeed();
	virtual double GetDamage();
	virtual int GetCadence();
	virtual int GetAmmo();
	virtual double GetLifeTime();
	virtual ~Turret();
protected:
	int ammo_;//balas que quedan en el cargador
	int maxAmmo_;//tamaño del cargador de la torreta, si es 0 la municion es infinita;
	int cadence_;//cadencia de disparo
	int reloadTime_;//tiempo de recarga al vaciar el cargador
	int speed_;//velocidad del proyectil
	int lastTimeReloaded_;
	int lastTimeShot_;
	double damage_;//daño de cada proyectil
	double lifeTime_; //tiempo de vida del proyectil
	proyectileType prType_;//tipo de proyectil
	string path_;//direccion del sprite de la torreta
	string animationpath_;
	ShootComponent* shC_;//codigo de disparo (en que forma dispara)
	FollowGameObject* followC_;
	Animation* animC_;
	Vehicle* car_;//coche al que esta pegada la torreta

};

