#pragma once
#include "GameState.h"
#include "Enemy.h"
#include "UI.h"
#include "TileMap.h"
#include "Money.h"
#include "FollowMiddlePoint.h"
#include "Respawner.h"
#include "Shop.h"

class Level2State : public GameState {
public:
	Level2State ();
	virtual ~Level2State ();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime);

	virtual void loadTilemap ();
	void awakeMap () { tilemap_->setSleep (false); }
private:
	// Tilemap
	TileMap *tilemap_;

	//camera logic
	FollowMiddlePoint* cameraFollow_;

	// Systems
	Respawner* respawner_;
};

