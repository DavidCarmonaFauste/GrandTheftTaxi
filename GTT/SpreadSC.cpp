#include "SpreadSC.h"


SpreadSC::SpreadSC(Turret * turret, double dispersionAngle, int numPellets) :ShootComponent(turret)
{
	dispersionAngle_ = dispersionAngle;
	numPellets_ = numPellets;
}

void SpreadSC::shoot()
{
	double ang = turret_->getRotation() / 180.0 * M_PI - (dispersionAngle_ / 180.0*M_PI / 2);

	ProyectilePool::GetInstance()->addShotgunB(turret_->getCenter(),
		Vector2D(sin(ang), -cos(ang)));
	double incrang = dispersionAngle_ / 180.0*M_PI / (numPellets_-1);
	ang += incrang;
	
	for (int i = 1; i < numPellets_; i++) {
		ProyectilePool::GetInstance()->addShotgunB(turret_->getCenter(),
			Vector2D((sin(ang)), (-cos(ang))));
		ang += incrang;
	}
}
