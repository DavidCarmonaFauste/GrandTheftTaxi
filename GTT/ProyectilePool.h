#pragma once
#include "GameObject.h"
#include "Proyectile.h"

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
	virtual Proyectile* addProyectile(Vector2D pos, Vector2D vel, proyectileType type=BULLET, double lifeTime=5000, double damage=10);
	virtual ~ProyectilePool();
private:
	ProyectilePool();
	static int const MAX_PROYECTILES = 100;
	Proyectile proyectiles_[MAX_PROYECTILES];
	Proyectile* getUnusedProyectile();
	static ProyectilePool* instance_;
};

