#pragma once
#include "GameObject.h"
#include "Proyectile.h"
#include <vector>

enum ProyectileType {
	GUNB,
	SHOTGUNB,
};

class ProyectilePool :public GameObject
{
public:
	ProyectilePool(ProyectilePool&) = delete;
	ProyectilePool& operator=(const ProyectilePool&) = delete;

	static ProyectilePool* GetInstance() {
		if (instance_ == nullptr) {
			instance_ = new ProyectilePool();
		}
		return instance_;
	}
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual Proyectile* addProyectile(Vector2D pos, Vector2D vel, ProyectileType prType);
	virtual ~ProyectilePool();
private:
	ProyectilePool();
	int standB = 0;
	int nStandBullets = 40;
	int sgB = standB + nStandBullets;
	int nShotGunBullets = 30;
	int spstandB = sgB + nShotGunBullets;
	int nSpecStandBullets = 10;
	int spsgB = spstandB + nSpecStandBullets;
	int nSpecSGBullets = 20;
	vector <Proyectile*> proyectiles_;
	Proyectile* getUnusedStandardB();
	Proyectile* getUnusedShotGunB();
	static ProyectilePool* instance_;
};

