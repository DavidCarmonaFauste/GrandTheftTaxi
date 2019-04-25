#include "EnemyManager.h"
#include "NodeMapsManager.h"

unique_ptr<EnemyManager> EnemyManager::instance_ = nullptr;

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::ReadEnemyInfo()
{
	enemyInfoFile_.open("../TextFiles/Enemies.txt");
	if (enemyInfoFile_.is_open()) {
		string line;
		string district;
		while (getline(enemyInfoFile_, line)) {
			istringstream row(line);
			switch (line[0]) {
			case'D': {
				row >> district;
				break;
			}
			case 'E': {
				string enemyid;
				string patrolid;
				string spawnid;
				row >> enemyid >> patrolid >> spawnid;
				Enemy* e = new Enemy(ENEMY1, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid]);
				enemies_[enemyid] = e;
				break;
			}
			default:
				break;
			}

		}
		enemyInfoFile_.close();
	}
}

void EnemyManager::addSpawn(string id, Vector2D pos)
{
	spawns_[id] = pos;
}

void EnemyManager::update(Uint32 deltaTime)
{
	for (auto e : enemies_) {
		if(e.second != nullptr)
		e.second->update(deltaTime);
	}
}

void EnemyManager::render(Uint32 deltaTime)
{
	for (auto e : enemies_) {
		if(e.second!=nullptr)
		e.second->render(deltaTime);
	}
}
