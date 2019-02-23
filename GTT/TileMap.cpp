#include "TileMap.h"



TileMap::TileMap() {

}


TileMap::~TileMap() {

}

void TileMap::handleInput(Uint32 deltaTime, const SDL_Event & event) {
	Container::handleInput(deltaTime, event);

	for (int y = 0; y < tiles_.size(); y++) {
		for (int x = 0; x < tiles_[y].size(); x++)
			tiles_[y][x]->handleInput(deltaTime, event);
	}
}

void TileMap::update(Uint32 deltaTime) {
	Container::update(deltaTime);

	for (int y = 0; y < tiles_.size(); y++) {
		for (int x = 0; x < tiles_[y].size(); x++)
			tiles_[y][x]->update(deltaTime);
	}
}

void TileMap::render(Uint32 deltaTime) {
	Container::render(deltaTime);

	for (int y = 0; y < tiles_.size(); y++) {
		for (int x = 0; x < tiles_[y].size(); x++)
			tiles_[y][x]->render(deltaTime);
	}
}

void TileMap::setTile(Tile * tile, int x, int y) {
	if (tiles_.size() > 0 && y < tiles_.size() && x < tiles_[0].size()) {
		delete tiles_[y][x];
		tiles_[y][x] = tile;
	}
}

Tile * TileMap::getTile(int x, int y)
{
	if (tiles_.size() > 0 && y < tiles_.size() && x < tiles_[0].size())
		return tiles_[y][x];
	else
		return nullptr;
}
