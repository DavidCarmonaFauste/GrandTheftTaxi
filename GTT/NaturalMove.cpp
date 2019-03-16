#include "NaturalMove.h"



NaturalMove::NaturalMove()
{
}

void NaturalMove::update(GameObject * o, Uint32 deltaTime)
{
	o->setPosition(o->getPosition() + o->getVelocity() * deltaTime);
}


NaturalMove::~NaturalMove()
{
}
