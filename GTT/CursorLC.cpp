#include "CursorLC.h"
#include "Game.h"
#include <iostream>


bool init = false;
bool creating = false;
bool finish = false;
Vector2D enemy_position = Vector2D(0, 0);
Vector2D start_position = enemy_position;
Vector2D wall[2] = { Vector2D(32, 32), Vector2D(320, 320) };

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
		Vector2D final = Vector2D(320, 640);
		cout << "\n -Point created...\n";
		cout << "\n Final = (" + to_string(final.x) + "," + to_string(final.y) + ")\n";
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

		while (!finish)
		{
			if(!(((enemy_position.x + 32) >= wall[0].x) && ((enemy_position.x + 32) <= wall[1].x) && ((enemy_position.y - 32) >= wall[0].y) && ((enemy_position.y - 32) <= wall[1].y)) && !search(close, Vector2D(enemy_position.x + 32, enemy_position.y - 32)))
				push(open, Vector2D(enemy_position.x + 32, enemy_position.y - 32), "open list"); //right-up -> 0

			if (!(((enemy_position.x + 32) >= wall[0].x) && ((enemy_position.x + 32) <= wall[1].x) && (enemy_position.y >= wall[0].y) && (enemy_position.y <= wall[1].y)) && !search(close, Vector2D(enemy_position.x + 32, enemy_position.y)))
				push(open, Vector2D(enemy_position.x + 32, enemy_position.y), "open list"); //right-middle -> 1

			if (!(((enemy_position.x + 32) >= wall[0].x) && ((enemy_position.x + 32) <= wall[1].x) && ((enemy_position.y + 32) >= wall[0].y) && ((enemy_position.y + 32) <= wall[1].y) && !search(close, Vector2D(enemy_position.x + 32, enemy_position.y + 32))))
				push(open, Vector2D(enemy_position.x + 32, enemy_position.y + 32), "open list"); //right-down -> 2

			if (!((enemy_position.x >= wall[0].x) && (enemy_position.x <= wall[1].x) && ((enemy_position.y - 32) >= wall[0].y) && ((enemy_position.y - 32) <= wall[1].y)) && !search(close, Vector2D(enemy_position.x, enemy_position.y - 32)))
				push(open, Vector2D(enemy_position.x, enemy_position.y - 32), "open list"); //middle-up -> 3

			if (!((enemy_position.x >= wall[0].x) && (enemy_position.x <= wall[1].x) && ((enemy_position.y + 32) >= wall[0].y) && ((enemy_position.y + 32) <= wall[1].y)) && !search(close, Vector2D(enemy_position.x, enemy_position.y + 32)))
				push(open, Vector2D(enemy_position.x, enemy_position.y + 32), "open list"); //middle-down -> 4

			if (!(((enemy_position.x - 32) >= wall[0].x) && ((enemy_position.x - 32) <= wall[1].x) && ((enemy_position.y - 32) >= wall[0].y) && ((enemy_position.y - 32) <= wall[1].y)) && !search(close, Vector2D(enemy_position.x - 32, enemy_position.y - 32)))
				push(open, Vector2D(enemy_position.x - 32, enemy_position.y - 32), "open list"); //left-up -> 5

			if (!(((enemy_position.x - 32) >= wall[0].x) && ((enemy_position.x - 32) <= wall[1].x) && (enemy_position.y >= wall[0].y) && (enemy_position.y <= wall[1].y)) && !search(close, Vector2D(enemy_position.x - 32, enemy_position.y)))
				push(open, Vector2D(enemy_position.x - 32, enemy_position.y), "open list"); //left-middle -> 6

			if (!(((enemy_position.x - 32) >= wall[0].x) && ((enemy_position.x - 32) <= wall[1].x) && ((enemy_position.y + 32) >= wall[0].y) && ((enemy_position.y + 32) <= wall[1].y)) && !search(close, Vector2D(enemy_position.x - 32, enemy_position.y + 32)))
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

			switch (vec_to_close)
			{
			case 0:
				cout << "\nGo to righ-up \n";
				break;
			case 1:
				cout << "\nGo to righ-middle \n";
				break;
			case 2:
				cout << "\nGo to righ-down \n";
				break;
			case 3:
				cout << "\nGo to middle-up \n";
				break;
			case 4:
				cout << "\nGo to middle-down \n";
				break;
			case 5:
				cout << "\nGo to left-up \n";
				break;
			case 6:
				cout << "\nGo to left-middle \n";
				break;
			case 7:
				cout << "\nGo to left-down \n";
				break;
			}

			push(close, find(open, vec_to_close), "close list");
			enemy_position = find(open, vec_to_close);

			open.clear();

			if((enemy_position.x < (final.x + 32) && enemy_position.x > (final.x - 32)) && (enemy_position.y < (final.y + 32) && enemy_position.y > (final.y - 32))) finish = true;
		}
		cout << "\n\n		THE END \n";
	}
	o->setPosition(Vector2D(((double)x/(double)Game::getInstance()->getWindowWidth())*(double)Game::getInstance()->getCameraWidth() - o->getWidth()/2,
		((double)y / (double)Game::getInstance()->getWindowHeight())*(double)Game::getInstance()->getCameraHeight()- o->getHeight()/2));
}

void CursorLC::push(std::list<Vector2D> &l, Vector2D v, string t)
{
	l.push_back(v);
	if(t == "close list")cout << "\nPushed x=" + std::to_string(v.x) + " y=" + std::to_string(v.y) + " at " + t + '\n';
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

bool CursorLC::search(std::list<Vector2D> l, Vector2D v)
{
	std::list<Vector2D>::iterator findIter = std::find(l.begin(), l.end(), v);
	if (findIter == l.end()) return false;
	else return true;
}

CursorLC::~CursorLC()
{
}
