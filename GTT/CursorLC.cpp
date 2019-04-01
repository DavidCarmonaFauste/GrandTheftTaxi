#include "CursorLC.h"
#include "Game.h"
#include <iostream>
#include <list>

bool init = false;
bool creating = false;
CursorLC::CursorLC()
{
}

void CursorLC::update(GameObject * o, Uint32 deltaTime)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if(!init)
	{
		init = true;
		cout << "init -> ";
		std::list<int> open;
		std::list<int> close;
		cout << "list created -> ";
		if (!creating)
		{
			creating = true;
			cout << "creting ->";
			
		}
	}
	o->setPosition(Vector2D(((double)x/(double)Game::getInstance()->getWindowWidth())*(double)Game::getInstance()->getCameraWidth() - o->getWidth()/2,
		((double)y / (double)Game::getInstance()->getWindowHeight())*(double)Game::getInstance()->getCameraHeight()- o->getHeight()/2));
}

void push(std::list<int> l)
{

}

CursorLC::~CursorLC()
{
}
