#pragma once
#include <map>

#include "Enemy.h"

using namespace std;
class EnemyManager
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
	void ReadEnemyInfo();
private:
	map<string, Enemy*> enemies_;
};

