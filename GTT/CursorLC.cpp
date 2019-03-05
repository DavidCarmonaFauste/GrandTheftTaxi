#include "CursorLC.h"



CursorLC::CursorLC()
{
}

void CursorLC::update(GameObject * o, Uint32 deltaTime)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	o->setPosition(Vector2D(x - o->getWidth() / 2, y - o->getHeight() / 2));
}


CursorLC::~CursorLC()
{
}
