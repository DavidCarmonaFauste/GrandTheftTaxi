#include "CursorLC.h"
#include "Game.h"
#include <iostream>


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
		cout << "init..." ;
		std::list<Vector2D> open;
		std::list<Vector2D> close;
		cout << "list created..." ;
		if (!creating)
		{
			creating = true;
			cout << "creting..." + '\n';
			push(open, Vector2D(0, 0), "open list");
			push(close, Vector2D(0, 0), "close list");
		}
	}
	o->setPosition(Vector2D(((double)x/(double)Game::getInstance()->getWindowWidth())*(double)Game::getInstance()->getCameraWidth() - o->getWidth()/2,
		((double)y / (double)Game::getInstance()->getWindowHeight())*(double)Game::getInstance()->getCameraHeight()- o->getHeight()/2));
}

void CursorLC::push(std::list<Vector2D> l, Vector2D v, string t)
{
	l.push_back(v);
	cout << "pushed x=" + std::to_string(v.x) + " y=" + std::to_string(v.y) + " at " + t + '\n';
}

CursorLC::~CursorLC()
{
}
