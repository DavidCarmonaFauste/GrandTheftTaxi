#include "AimAtTaxi.h"
#include "Vehicle.h"



AimAtTaxi::~AimAtTaxi()
{
}

void AimAtTaxi::update(GameObject * o, Uint32 deltaTime)
{
	double disX = Vehicle::GetInstance()->getPosition().x + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().x - o->getCenter().x;
	double disY = Vehicle::GetInstance()->getCenter().y + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().y - o->getCenter().y;
	double degrees = acos(-disY / (sqrt(pow(disX, 2) + pow(disY, 2))));
	o->setRotation(degrees * 180.0 / M_PI);
	if (disX < 0)
		o->setRotation(-o->getRotation());
}
