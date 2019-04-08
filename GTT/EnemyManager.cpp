#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
	numberOfEnemies = 0;
}


EnemyManager::~EnemyManager()
{
}

Enemy * EnemyManager::Get_Enemy(int position)
{
	//return 	enemyList[position];
}

void EnemyManager::Add_Enemy(int x, int y, VehicleInfo r)
{
	//enemyList.insert(new Enemy(x, y, r));
	numberOfEnemies++;
}

int EnemyManager::getNumberOfEnemies()
{
	return 0;
}
