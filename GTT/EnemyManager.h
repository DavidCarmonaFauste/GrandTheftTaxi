#pragma once
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "Enemy.h"


using namespace std;
class EnemyManager:public Container
{
	EnemyManager(EnemyManager &) = delete;
	EnemyManager & operator=(const EnemyManager &) = delete;

	static unique_ptr<EnemyManager> instance_; //ptr instance class
public:
	EnemyManager();
	virtual ~EnemyManager();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new EnemyManager());
		}
	}
	//get singleton class
	inline static EnemyManager* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

	void ReadEnemyInfo();
	void addSpawn(string id, Vector2D pos);
	void deactivateIA();
	bool EnemyAtPos(Vector2D pos, GameObject* enemy=nullptr);

	int getEnemyCount();
	int getTotalEnemies () const { return totalEnemies_; }
	int getLevel1Enemies () const { return enemiesLvl1_; }
	int getLevel2Enemies () const { return enemiesLvl2_; }
	virtual void update(Uint32 deltaTime);
	virtual void render(Uint32 deltaTime);
	virtual void input(Uint32 time, const SDL_Event & event);

	void setLevel (char c) { level_ = c; }

private:
	map<string, Enemy*> enemies_;
	map<string, Vector2D> spawns_;
	ifstream enemyInfoFile_;

	char level_;
	bool readOnce_ = false;
	int enemiesLvl1_ = 0;
	int enemiesLvl2_ = 0;
	int totalEnemies_ = 0;
};

