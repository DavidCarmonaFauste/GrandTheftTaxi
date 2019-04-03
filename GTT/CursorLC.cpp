#include "CursorLC.h"
#include "Game.h"
#include <iostream>


bool init = false;
bool creating = false;
bool finish = false;
Vector2D enemy_position = Vector2D(0, 0);
Vector2D start_position = enemy_position;
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
		cout << "\n -Init...\n";
		std::list<Vector2D> open;
		std::list<Vector2D> close;
		cout << "\n -List created...\n" ;
		Vector2D final = Vector2D(340, 400);
		cout << "\n -Point created...\n";
		if (!creating)
		{
			creating = true;
			cout << "\n -Creting...\n";
			//push(open, enemy_position, "open list");
			push(close, enemy_position, "close list");
		}
		cout << "\n -Distance calculated...\n";
		Vector2D distance = Vector2D(enemy_position.x - final.x, enemy_position.y - final.y);
		cout << "\n X = " + std::to_string(distance.x)  + "\n Y = " + std::to_string(distance.y)  + "\n";
		/*char direcction;
		if (abs(distance.x) > abs(distance.y))
		{
			if (distance.x > 0) direcction = 'r';
			else direcction = 'l';
		}
		else
		{
			if (distance.y > 0) direcction = 'u';
			else direcction = 'd';
		}
		cout << "\n -Direcction calculated...\n";
		string d;
		d.push_back(direcction);
		cout << "\nDirecction = " + d + "\n";*/
		while (!finish)
		{
			

			

			push(open, Vector2D(enemy_position.x + 32, enemy_position.y - 32), "open list"); //right-up -> 0
			push(open, Vector2D(enemy_position.x + 32, enemy_position.y), "open list"); //right-middle -> 1
			push(open, Vector2D(enemy_position.x + 32, enemy_position.y + 32), "open list"); //right-down -> 2
			push(open, Vector2D(enemy_position.x, enemy_position.y - 32), "open list"); //middle-up -> 3
			push(open, Vector2D(enemy_position.x, enemy_position.y + 32), "open list"); //middle-down -> 4
			push(open, Vector2D(enemy_position.x - 32, enemy_position.y - 32), "open list"); //left-up -> 5
			push(open, Vector2D(enemy_position.x - 32, enemy_position.y), "open list"); //left-middle -> 6
			push(open, Vector2D(enemy_position.x - 32, enemy_position.y + 32), "open list"); //left-down -> 7

			int minum = 999;
			int vec_to_close = -1;
			for (int i = 0; i < 8; i++)
			{
				Vector2D actual_Vect = find(open, i);

				int h = abs(actual_Vect.x - final.x) + abs(actual_Vect.y - final.y);
				int g = sqrtf(abs(enemy_position.x - actual_Vect.x) + abs(enemy_position.y - actual_Vect.y));
				int f = h + g;

				if (f < minum)
				{
					minum = f;
					vec_to_close = i;
				}
			}

			/*
			if (abs(distance.x) > abs(distance.y))
			{
				if (distance.x > 0) direcction = 'r';
				else direcction = 'l';
			}
			else
			{
				if (distance.y > 0) direcction = 'u';
				else direcction = 'd';
			}*/
			finish = true;
		}
	}
	o->setPosition(Vector2D(((double)x/(double)Game::getInstance()->getWindowWidth())*(double)Game::getInstance()->getCameraWidth() - o->getWidth()/2,
		((double)y / (double)Game::getInstance()->getWindowHeight())*(double)Game::getInstance()->getCameraHeight()- o->getHeight()/2));
}

void CursorLC::push(std::list<Vector2D> &l, Vector2D v, string t)
{
	l.push_back(v);
	cout << "\nPushed x=" + std::to_string(v.x) + " y=" + std::to_string(v.y) + " at " + t + '\n';
}

Vector2D CursorLC::find(std::list<Vector2D> l, int c)
{
	int i = 0;
	for (auto v : l)
	{
		if (i == c) return v;
		i++;
	}

	return Vector2D(-999,-999);
}

CursorLC::~CursorLC()
{
}
