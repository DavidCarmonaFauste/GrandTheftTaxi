#pragma once
#include "GameState.h"
#include "Vehicle.h"
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

	virtual void update (Uint32 deltaTime);
private:
	// Tilemap
	TileMap *tilemap_;

	// Vehicles
	Vehicle* taxi_;
	FollowGameObject* cameraFollow_;

	// Systems
	Money* moneySystem_;
	Respawner* respawner_;

	// UI
	UI* UI_;
};

