#pragma once

#include <vector>

#include "Container.h"
#include "Tile.h"

class TileMap :	public Container {
public:
	TileMap();
	virtual ~TileMap();

	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event) override;
	virtual void update(Uint32 deltaTime) override;
	virtual void render(Uint32 deltaTime) override;

	void setTile(Tile* tile, int x, int y);
	Tile* getTile(int x, int y);

private:
	vector<vector<Tile*>> tiles_;
};

