#include "Vehicle.h"
#include "Turret.h"
#include "AimAtCursorAC.h"

Vehicle::Vehicle(Resources::VehicleId id) {
	Resources::VehicleInfo& r = Resources::getInstance()->vehicles_[id];

	this->setWidth(r.width);
	this->setHeight(r.height);

	setPosition(Vector2D(100, 0));

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(100);
	addLogicComponent(health_);

	aimC_ = new AimAtCursorAC();
}


Vehicle::~Vehicle() {
	delete phyO_; phyO_ = nullptr;
	delete sprite_; sprite_ = nullptr;
	delete currentTurret_; currentTurret_ = nullptr;
	delete health_; health_ = nullptr;
}

Health * Vehicle::getHealthComponent() {
	return health_;
}

AimComponent * Vehicle::GetAimComponent()
{
	return aimC_;
}

void Vehicle::Shoot()
{
	currentTurret_->Shoot();
}

void Vehicle::Reload()
{
	currentTurret_->InitiateReload();
}

void Vehicle::EquipTurret(Turret * turret)
{
	currentTurret_ = turret;
	currentTurret_->AttachToVehicle(this);
}

void Vehicle::setPosition(const Vector2D & pos, bool force) {
	GameObject::setPosition(pos);

	if (force) {
		b2Vec2 nextPos = b2Vec2(pos.x, pos.y) +
			b2Vec2(phyO_->getOrigin().x * width_,
				phyO_->getOrigin().y * height_);

		nextPos = b2Vec2(nextPos.x * Resources::getInstance()->physicsScalingFactor,
			nextPos.y * Resources::getInstance()->physicsScalingFactor);

		phyO_->getBody()->SetTransform(nextPos, phyO_->getBody()->GetAngle());
	}
}

void Vehicle::handleInput(Uint32 time, const SDL_Event & event)
{	
	if(currentTurret_!=nullptr) currentTurret_->handleInput(time, event);
	Container::handleInput(time, event);
}

void Vehicle::update(Uint32 time) {	
	if (currentTurret_ != nullptr)
		currentTurret_->update(time);

	Container::update(time);
}

void Vehicle::render(Uint32 time) {
	Container::render(time);

	if (currentTurret_ != nullptr)
		currentTurret_->render(time);
}

