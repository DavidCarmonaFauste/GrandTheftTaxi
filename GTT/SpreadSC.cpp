#include "SpreadSC.h"
#define PI 3.14159265359


SpreadSC::SpreadSC(ProyectilePool * bPool, Turret * turret, double dispersionAngle, int numPellets) :ShootComponent(bPool, turret)
{
	dispersionAngle_ = dispersionAngle;
	numPellets_ = numPellets;
}

void SpreadSC::shoot()
{
	double ang = turret_->getRotation() / 180.0 * PI - (dispersionAngle_ / 180.0*PI / 2);

	bPool_->addProyectile(turret_->getCenter(),
		Vector2D(turret_->GetSpeed()*sin(ang), -turret_->GetSpeed()*cos(ang)),
		turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
	double incrang = dispersionAngle_ / 180.0*PI / (numPellets_-1);
	ang += incrang;
	
	for (int i = 1; i < numPellets_; i++) {
		bPool_->addProyectile(turret_->getCenter(), 
			Vector2D(turret_->GetSpeed()*sin(ang), -turret_->GetSpeed()*cos(ang)), turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
		ang += incrang;
	}
	
	

	/*
	double ang = turret_->getRotation() / 180.0 * PI - (dispersionAngle_/180.0*PI/2);
	bPool_->addProyectile(turret_->getPosition(),
		Vector2D(turret_->GetSpeed()*sin(ang), -turret_->GetSpeed()*cos(ang)),
		turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
	ang += dispersionAngle_/180.0*PI;
	bPool_->addProyectile(turret_->getPosition(), Vector2D(turret_->GetSpeed()*sin(ang), -turret_->GetSpeed()*cos(ang)), turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
	*/


}
