#pragma once
#include "GameState.h"
#include "Vehicle.h"
#include "UI.h"
#include "TileMap.h"
#include "Money.h"
#include "FollowGameObject.h"

class MainState :
	public GameState
{
public:
	MainState();
	virtual ~MainState();

private:
	// Tilemap
	TileMap *tilemap_;

	// Vehicles
	Vehicle* taxi_;
	FollowGameObject* cameraFollow;

	// Systems
	Money* moneySystem;

	// UI
	UI* UI_;
};

