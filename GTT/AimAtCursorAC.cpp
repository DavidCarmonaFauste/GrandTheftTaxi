#include "AimAtCursorAC.h"
#include "Reticule.h"

void AimAtCursorAC::update(GameObject * o, Uint32 deltaTime)
{
	double disX = Reticule::GetInstance()->getCenter().x - o->getCenter().x;
	double disY = Reticule::GetInstance()->getCenter().y - o->getCenter().y;
	double degrees = acos(-disY / (sqrt(pow(disX, 2) + pow(disY, 2))));
	o->setRotation(degrees * 180.0 / M_PI);
	if (disX < 0)
		o->setRotation(-o->getRotation());
}
