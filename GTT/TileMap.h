#pragma once

#include <vector>
#include <map>

#include "Container.h"
#include "Tile.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

class TileMap :	public Container {
public:
	TileMap(string path);
	virtual ~TileMap();

	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event) override;
	virtual void update(Uint32 deltaTime) override;
	virtual void render(Uint32 deltaTime) override;

	void setTile(Tile* tile, int layer, int x, int y);
	Tile* getTile(int layer, int x, int y);

private:
	map<int, Texture*> tilesets_;
	vector<vector<vector<Tile*>>> layers_;
	SDL_Rect tileDest;
	void tmxToScene();

	tmx::Map* tmxMap_;
};

