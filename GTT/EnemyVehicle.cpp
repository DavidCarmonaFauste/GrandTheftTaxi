#include "EnemyVehicle.h"



EnemyVehicle::EnemyVehicle(int x, int y, Resources::VehicleId id)
{
}


EnemyVehicle::~EnemyVehicle()
{
}

PhysicObject * EnemyVehicle::GetPhyO()
{
	return phyO_;
}

float32 EnemyVehicle::GetMaxSpeed()
{
	return maxSpeed_;
}

float32 EnemyVehicle::GetTurnSpeed()
{
	return turnSpeed_;
}

float32 EnemyVehicle::GetAcceleration()
{
	return acceleration_;
}

Health * EnemyVehicle::getHealthComponent()
{
	return health_;
}

void EnemyVehicle::EquipTurret(Turret * turret)
{
	gun_ = turret;
}

Turret * EnemyVehicle::getCurrentTurret()
{
	return gun_;
}

void EnemyVehicle::setPosition(const Vector2D & pos)
{
	position_ = pos;
}

void EnemyVehicle::handleInput(Uint32 time, const SDL_Event & event)
{
}

void EnemyVehicle::render(Uint32 time)
{
}

void EnemyVehicle::update(Uint32 time)
{
}


