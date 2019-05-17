#include "TileMap.h"
#include "Vehicle.h"
#include "NodeMapsManager.h"
#include "EnemyManager.h"
#include "ShopManager.h"
#include "BridgeManager.h"

TileMap::TileMap(string path) {
	// Loads the tmx map from the given path
	// and converts it into GameObjects
	tmxMap_ = tmx::Map();
	tmxMap_.load(path);

	string imagePath = path.substr(0, path.size() - 3).append("png");
	int w = tmxMap_.getTileSize().x * tmxMap_.getTileCount().x;
	int h = tmxMap_.getTileSize().y * tmxMap_.getTileCount().y;
	setWidth(w); setHeight(h); setPosition(Vector2D(0, 0));

	mapSprite_ = new Sprite(imagePath, w, h, 0, 0);
	mapSprite_->setAutoPos(false);
	mapSprite_->setAutoSize(false);
	addRenderComponent(mapSprite_);

	phyO_ = new PhysicObject(b2_staticBody, 0, 0, 0, 0, false);
	tmxToScene();

	setSleep (true);
}

TileMap::~TileMap() {
	delete mapSprite_; mapSprite_ = nullptr;
	delete phyO_; phyO_ = nullptr;
}

void TileMap::tmxToScene() {
	// Iterate through all object layers and convert them to
	// containers
	const auto& layers = tmxMap_.getLayers();
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
}

bool TileMap::processObject(string layerName, const tmx::Object &object) {
	if (layerName == "Collisions1") return processCollision(object, '1');
	if (layerName == "CollisionsOpen") return processCollision(object, 'o');
	if (layerName == "Collisions2") return processCollision(object, '2');

	if (layerName == "Player1") return processPlayer(object, '1');
	if (layerName == "Player1Open") return processPlayer (object, 'o');
	if (layerName == "Player2") return processPlayer (object, '2');

	if (layerName == "Bridge1") return processBridge (object, '1');
	if (layerName == "Bridge2") return processBridge (object, '2');

	if (layerName == "Gas") return processGas(object);
	if (layerName == "Enemies") return processSpawns(object);
	
	else return processNodes(object, layerName);
}

bool TileMap::processCollision(const tmx::Object &object, char level) {
	b2PolygonShape shape = b2PolygonShape();
	b2FixtureDef fixDef;
	tmx::FloatRect box = object.getAABB();
	tmx::Vector2f pos = object.getPosition();
	Vector2D size = Vector2D(box.width / 2 * PHYSICS_SCALING_FACTOR,
		box.height / 2 * PHYSICS_SCALING_FACTOR);

	shape.SetAsBox(size.x, size.y, Vector2D(pos.x * PHYSICS_SCALING_FACTOR + size.x,
		pos.y*PHYSICS_SCALING_FACTOR + size.y), 0);
	fixDef.shape = &shape;
	phyO_->getBody()->CreateFixture(&fixDef);

	if (level == '1')		
		phyO_->setCollisions(TILES_GROUP_LVL_1, TILE_CATEGORY);
	else if (level == 'o')	
		phyO_->setCollisions(TILES_GROUP_LVL_1_OPEN, LEVEL_1_CATEGORY);
	else if (level == '2')	
		phyO_->setCollisions(TILES_GROUP_LVL_2, LEVEL_2_CATEGORY);
	
	phyO_->getBody()->GetFixtureList()->SetFriction(ENVIRONMENT_FRICTION);

	return false;
}

bool TileMap::processPlayer(const tmx::Object & object, char level) {
	if (Vehicle::getInstance ()->GetPhyO () == nullptr) {
		Vehicle::getInstance ()->initAtributtes (THECOOLERTAXI, DEFAULT_KEYS);
	}

	Vector2D pos = Vector2D(object.getPosition().x, object.getPosition().y);
	
	if (level == '1')		Vehicle::getInstance ()->setLevel1SpawnPoint (pos);
	else if (level == 'o')	Vehicle::getInstance ()->setLevel1OpenSpawnPoint (pos);
	else if (level == '2')	Vehicle::getInstance ()->setLevel2SpawnPoint (pos);

	return true;
}

bool TileMap::processGas(const tmx::Object & object) {
	Shop *shop = new Shop(object.getAABB().width, object.getAABB().height, object.getPosition().x, object.getPosition().y);
	ShopManager::getInstance()->addShop(shop);

	return false;
}

bool TileMap::processNodes(const tmx::Object & object, string layerName)
{
	if (!NodeMapsManager::getInstance()->NodeMapExists(layerName)) NodeMapsManager::getInstance()->addNodeMap(layerName);
	Node* node = new Node(Vector2D(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y + object.getAABB().height / 2), object.getName());
	NodeMapsManager::getInstance()->getNodeMap(layerName)->addNode(node, object.getName());
	return false;
}

bool TileMap::processSpawns(const tmx::Object & object)
{
	EnemyManager::getInstance()->addSpawn(object.getName(), Vector2D(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y + object.getAABB().height / 2));
	return false;
}

bool TileMap::processBridge (const tmx::Object & object, char level) {
	Bridge *bridge = new Bridge (object.getAABB ().width, object.getAABB ().height, object.getPosition ().x, object.getPosition ().y);
	
	BridgeManager::getInstance ()->setBridge (bridge, level);

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

void TileMap::setSleep (bool flag) {
	active_ = !flag;
	phyO_->getBody ()->SetActive (!flag);
}

