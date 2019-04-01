#pragma once
#include "GameObject.h"
#include "Proyectile.h"
#include <vector>

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
	virtual Proyectile* addProyectile(Vector2D pos, Vector2D vel, ProyectileInfo prType);
	virtual ~ProyectilePool();
private:
	ProyectilePool();
	static const int MAXPROYECTILES = 100;
	Proyectile proyectiles_[MAXPROYECTILES];
	Proyectile* getUnusedProyectile();
	static ProyectilePool* instance_;
};

