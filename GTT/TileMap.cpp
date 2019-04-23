#include "TileMap.h"
#include "Vehicle.h"

TileMap::TileMap(string path) {
	// Loads the tmx map from the given path
	// and converts it into GameObjects
	tmxMap_ = new tmx::Map();
	tmxMap_->load(path);

	string imagePath = path.substr(0, path.size() - 3).append("png");
	int w = tmxMap_->getTileSize().x * tmxMap_->getTileCount().x;
	int h = tmxMap_->getTileSize().y * tmxMap_->getTileCount().y;
	setWidth(w); setHeight(h); setPosition(Vector2D(0, 0));

	mapSprite_ = new Sprite(imagePath, w, h, 0, 0);
	mapSprite_->setAutoPos(false);
	mapSprite_->setAutoSize(false);
	addRenderComponent(mapSprite_);

	phyO_ = new PhysicObject(b2_staticBody, 0, 0, 0, 0, false);
	tmxToScene();
}

TileMap::~TileMap() {
	delete tmxMap_; tmxMap_ = nullptr;
}

void TileMap::tmxToScene() {
	// Iterate through all object layers and convert them to
	// containers
	const auto& layers = tmxMap_->getLayers();
	for (const auto& layer : layers) {
		
		// Process only object layers
		if (layer->getType() == tmx::Layer::Type::Object) {
			cout << "Info: loading object layer " + layer->getName() + "\n";

			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects) {
				if (processObject(layer->getName(), object)) break;
			}
		}
	}
	cout << "Info: map load finished\n";
}

bool TileMap::processObject(string layerName, const tmx::Object &object) {
	if (layerName == "Collisions") return processCollision(object);
	if (layerName == "Player") return processPlayer(object);
}

bool TileMap::processCollision(const tmx::Object &object) {
	b2PolygonShape *shape = new b2PolygonShape();
	b2FixtureDef fixDef;
	tmx::FloatRect box = object.getAABB();
	tmx::Vector2f pos = object.getPosition();
	Vector2D size = Vector2D(box.width / 2 * PHYSICS_SCALING_FACTOR,
							 box.height / 2 * PHYSICS_SCALING_FACTOR);

	shape->SetAsBox(size.x, size.y, Vector2D(pos.x * PHYSICS_SCALING_FACTOR + size.x,
											 pos.y*PHYSICS_SCALING_FACTOR + size.y), 0);
	fixDef.shape = shape;
	phyO_->getBody()->CreateFixture(&fixDef);

	phyO_->setCollisions(TILES_GROUP, TILE_CATEGORY);
	phyO_->getBody()->GetFixtureList()->SetFriction(ENVIRONMENT_FRICTION);

	return false;
}

bool TileMap::processPlayer(const tmx::Object & object) {
	Vector2D pos = Vector2D(object.getPosition().x * PHYSICS_SCALING_FACTOR,
							object.getPosition().y * PHYSICS_SCALING_FACTOR);
	Vehicle::getInstance()->GetPhyO()->getBody()->SetTransform(pos, 0);

	return true;
}

bool TileMap::processGas(const tmx::Object & object) {
	return false;
}


void TileMap::handleInput(Uint32 deltaTime, const SDL_Event & event) {
	Container::handleInput(deltaTime, event);
}

void TileMap::update(Uint32 deltaTime) {
	Container::update(deltaTime);

}

void TileMap::render(Uint32 deltaTime) {
	Container::render(deltaTime);
}

