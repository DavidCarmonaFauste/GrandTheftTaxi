#pragma once
#include <list>

#include "Enemy.h"

using namespace std;
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();
	Enemy* Get_Enemy(int position);
	void Add_Enemy(int x, int y, VehicleInfo r);
	int getNumberOfEnemies();
private:
	list<Enemy*>enemyList;
	int numberOfEnemies;
	
};

