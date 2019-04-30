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
				string type;
				row >> enemyid >> patrolid >> spawnid >> type;
				Enemy* e;
				if (type == "Type1") {
					e = new Enemy(ENEMY1, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid], GUN);
					enemies_[enemyid] = e;
				}
				else if (type == "Type2") {
					e = new Enemy(ENEMY2, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid],SHOTGUN);
					enemies_[enemyid] = e;
				}
				else if (type == "Type3") {
					e = new Enemy(ENEMY3, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid], GUN);
					enemies_[enemyid] = e;
				}
				else if (type == "Type4") {
					e = new Enemy(ENEMYTANK, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid], SHOTGUN);
					enemies_[enemyid] = e;
				}
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
