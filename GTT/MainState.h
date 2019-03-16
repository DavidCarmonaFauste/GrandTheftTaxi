#pragma once
#include "GameState.h"
#include "Vehicle.h"
#include "UI.h"
#include "TileMap.h"

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

	// UI
	UI* UI_;
};

