#pragma once
#include "GameState.h"

#include "Enemy.h"
#include "UI.h"
#include "TileMap.h"
#include "Money.h"
#include "FollowGameObject.h"
#include "Respawner.h"
#include "Shop.h"

class MainState :
	public GameState
{
public:
	MainState();
	virtual ~MainState();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime);

private:
	// Tilemap
	TileMap *tilemap_;

	// Vehicles
	//Enemy* enemy1_;

	//camera logic
	FollowGameObject* cameraFollow;

	// Systems
	Respawner* respawner_;
};

