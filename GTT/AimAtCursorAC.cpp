#include "AimAtCursorAC.h"
#include "Reticule.h"
#define PI 3.14159265359

void AimAtCursorAC::update(GameObject * o, Uint32 deltaTime)
{
	double disX = Reticule::GetInstance()->getCenter().getX() - o->getCenter().getX();
	double disY = Reticule::GetInstance()->getCenter().getY() - o->getCenter().getY();
	double degrees = acos(-disY / (sqrt(pow(disX, 2) + pow(disY, 2))));
	o->setRotation(degrees * 180.0 / PI);
	if (disX < 0)
		o->setRotation(-o->getRotation());
}
