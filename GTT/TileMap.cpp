#include "TileMap.h"

TileMap::TileMap(string path) {
	// Loads the tmx map from the given path
	// and converts it into GameObjects
	tmxMap_ = new tmx::Map();
	tmxMap_->load(path);
	tmxToScene();
}

TileMap::~TileMap() {
	// Delete the tiles of each layer
	for (auto layer : layers_) {
		for (int y = 0; y < layer.second.size(); y++) {
			for (int x = 0; x < layer.second[y].size(); x++) {
				delete layer.second[y][x];
				layer.second[y][x] = nullptr;
			}
		}
	}

	delete tmxMap_; tmxMap_ = nullptr;
}

void TileMap::tmxToScene() {
	// Get the tile size
	tileDest.w = tmxMap_->getTileSize().x; // Tile width
	tileDest.h = tmxMap_->getTileSize().y; // Tile height

	// Load every tileset as a new texture
	auto& map_tilesets = tmxMap_->getTilesets();
	for (auto& tset : map_tilesets) {
		cout << "Info: loading tileset " + tset.getImagePath() + "\n";
		Texture* tex = new Texture(Game::getInstance()->getRenderer(), tset.getImagePath());
		tilesets_.insert(pair<uint32_t, Texture*>(tset.getFirstGID(), tex));
	}

	// Iterate through all layers and convert objects/tiles
	// into GameObjects
	const auto& layers = tmxMap_->getLayers();
	for (const auto& layer : layers) {
		
		// Object layers
		if (layer->getType() == tmx::Layer::Type::Object) {
			cout << "Info: loading object layer " + layer->getName() + "\n";

			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects) {
				// do stuff with object properties
				// UNUSED !!!
			}
		}
		 
		// Tile layers
		else if (layer->getType() == tmx::Layer::Type::Tile) {
			cout << "Info: loading tile layer " + layer->getName() + "\n";

			const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
			string layerName = tileLayer.getName();
			layers_[layerName] = vector<vector<Tile*>>();
			bool collision = tileLayer.getName() == "Collisions";

			// Iterate through every tile and instantiate it in the game
			for (int y = 0; y < tmxMap_->getTileCount().y; y++) {
				layers_[layerName].push_back(vector<Tile*>());

				for (int x = 0; x < tmxMap_->getTileCount().x; x++) {
					int tile_index = x + y * tmxMap_->getTileCount().x;
					uint32_t gid = tileLayer.getTiles()[tile_index].ID;

					// Empty tile
					if (gid == 0) {
						layers_[layerName][y].push_back(nullptr);
						continue;
					}

					// Look for the tileset that this tile uses
					// TILESET MUST BE ORDERED FROM LOWER TO HIGHER !
					auto tset_gid = -1;
					for (auto& ts : tilesets_) {
						if (ts.first <= gid) {
							tset_gid = ts.first;
							break;
						}
					}

					// Tileset not found
					if (tset_gid == -1) {
						layers_[layerName][y].push_back(nullptr);
						continue;
					}

					// Normalize the gid
					uint32_t norm_gid = gid - tset_gid;

					int tset_w = tilesets_[tset_gid]->getWidth();
					int tset_h = tilesets_[tset_gid]->getHeight();
					SDL_Rect* clip = new SDL_Rect();

					// Calculate the destination rect using tile size
					tileDest.x = tileDest.w * x;
					tileDest.y = tileDest.h * y;

					// Set the clipping rect to use the area of the
					// tileset
					clip->w = tileDest.w;
					clip->h = tileDest.h;
					clip->x = (norm_gid % (tset_w / tileDest.w)) * tileDest.w;;
					clip->y = (gid / (tset_w / tileDest.h)) * tileDest.h;

					Tile* tile = new Tile(tilesets_[tset_gid], &tileDest, clip, gid, collision);
					layers_[layerName][y].push_back(tile);
				}
			}

		}
	}
	cout << "Info: map load finished\n";
}

void TileMap::handleInput(Uint32 deltaTime, const SDL_Event & event) {
	Container::handleInput(deltaTime, event);

	// In case it's needed for every tile to handle input
	// HEAVY PROCCESSING LOAD !!

	/*
	for (int layer = 0; layer < layers_.size(); layer++) {
		for (int y = 0; y < layers_[layer].size(); y++) {
			for (int x = 0; x < layers_[layer][y].size(); x++)
				if (layer.second[y][x] != nullptr) layers_[layer][y][x]->handleInput(deltaTime, event);
		}
	}
	*/
}

void TileMap::update(Uint32 deltaTime) {
	Container::update(deltaTime);

	// In case it's needed for every tile to update
	// HEAVY PROCCESSING LOAD !!

	/*
	for (int layer = 0; layer < layers_.size(); layer++) {
		for (int y = 0; y < layers_[layer].size(); y++) {
			for (int x = 0; x < layers_[layer][y].size(); x++)
				if (layer.second[y][x] != nullptr) layers_[layer][y][x]->update(deltaTime);
		}
	}
	*/
}

void TileMap::render(Uint32 deltaTime) {
	Container::render(deltaTime);

	// Render every tile
	for (auto layer : layers_) {
		for (int y = 0; y < layer.second.size(); y++) {
			for (int x = 0; x < layer.second[y].size(); x++) {
				if (layer.second[y][x] != nullptr) layer.second[y][x]->render(deltaTime);
			}
		}
	}
}

vector<string> TileMap::getLayerNames() {
	vector<string> names;
	for (auto layer : layers_) {
		names.push_back(layer.first);
	}

	return names;
}

vector<vector<Tile*>> TileMap::getLayer(string layer) {
	return layers_[layer];
}

void TileMap::setTile(Tile * tile, string layer, int x, int y) {
	if (layers_.find(layer) != layers_.end() &&
		y < layers_[layer].size() && x < layers_[layer].size()) {

		delete layers_[layer][y][x];
		layers_[layer][y][x] = tile;
	}
}

Tile * TileMap::getTile(string layer, int x, int y) {
	if (layers_.find(layer) != layers_.end() &&
			y < layers_[layer].size() && x < layers_[layer].size())
		return layers_[layer][y][x];
	else
		return nullptr;
}
