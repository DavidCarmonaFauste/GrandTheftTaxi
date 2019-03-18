#pragma once
#include "GameObject.h"
#include "Projectile.h"

class ProjectilePool :public GameObject
{
public:
	ProjectilePool(ProjectilePool&) = delete;
	ProjectilePool& operator=(const ProjectilePool&) = delete;

	static ProjectilePool* GetInstance() {
		if (instance_ == nullptr) {
			instance_ = new ProjectilePool();
		}
		return instance_;
	}
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual Projectile* addProjectile(Vector2D pos, Vector2D vel, projectileType type=BULLET, double lifeTime=5000, double damage=10);
	virtual ~ProjectilePool();
private:
	ProjectilePool();
	static int const MAX_PROJECTILES = 100;
	Projectile projectiles_[MAX_PROJECTILES];
	Projectile* getUnusedProjectile();
	static ProjectilePool* instance_;
};

