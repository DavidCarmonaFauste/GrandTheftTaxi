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

	// Set the '(x, y)' tile of the layer 'layer' to the given one
	void setTile(Tile* tile, int layer, int x, int y);

	// Gets the '(x, y)' tile of the layer 'layer'
	Tile* getTile(int layer, int x, int y);

private:
	map<int, Texture*> tilesets_;
	vector< vector<vector<Tile*>> > layers_; // Layers (vector1) of columns (v2) and rows (v3)
	SDL_Rect tileDest;

	// Reads the already parsed tmx map and
	// creates the correspondent GameObjects
	void tmxToScene();

	tmx::Map* tmxMap_;
};
