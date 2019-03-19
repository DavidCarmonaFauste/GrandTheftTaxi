#include "Vehicle.h"
#include "Turret.h"
#include "AimAtCursorAC.h"
#include "ShootIC.h"
#include "ReloadInputComponent.h"
#include "ChangeWeaponIC.h"
#include "Reticule.h"

Vehicle::Vehicle(Resources::VehicleId id) {
	Resources::VehicleInfo& r = Resources::getInstance()->vehicles_[id];

	this->setWidth(r.width);
	this->setHeight(r.height);

	setPosition(Vector2D(400, 300));

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(100);
	addLogicComponent(health_);

	aimC_ = new AimAtCursorAC();
	addInputComponent(new ShootIC());
	addInputComponent(new ReloadInputComponent());
	addInputComponent(new ChangeWeaponIC());

	for (int i = 0; i < MAXTURRETS; i++) {
		turrets_[i]=nullptr;
	}
}


Vehicle::~Vehicle() {
	delete phyO_; phyO_ = nullptr;
	delete sprite_; sprite_ = nullptr;
	delete health_; health_ = nullptr;
	for (int i = 0; i < MAXTURRETS; i++) {
		delete turrets_[i];
	}
	delete[]turrets_;
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
	turrets_[currentTurret_]->Shoot();
}

void Vehicle::Reload()
{
	turrets_[currentTurret_]->InitiateReload();
}

void Vehicle::EquipTurret(Turret * turret)
{
	if (turrets_[currentTurret_] == nullptr) {
		turrets_[currentTurret_] = turret;
		Reticule::GetInstance()->ChangeReticule(turrets_[currentTurret_]->GetReticule());
		turrets_[currentTurret_]->AttachToVehicle(this);

	}
	else if (currentTurret_ < MAXTURRETS - 1 && turrets_[currentTurret_ + 1] == nullptr) {
		turrets_[currentTurret_+1] = turret;
		turrets_[currentTurret_+1]->AttachToVehicle(this);
	}
	else {
		cout << "maximo numero de torretas alcanzado" << endl;
	}
}
void Vehicle::ChangeTurret()
{
	currentTurret_ = (currentTurret_ + 1)% MAXTURRETS;
	Reticule::GetInstance()->ChangeReticule(turrets_[currentTurret_]->GetReticule());
}
Turret * Vehicle::getCurrentTurret()
{
	return turrets_[currentTurret_];
}

void Vehicle::setPosition(const Vector2D & pos, bool force) {
	GameObject::setPosition(pos);

	if (force) {
		b2Vec2 nextPos = b2Vec2(pos.getX(), pos.getY()) +
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

	if (turrets_[currentTurret_] != nullptr)
		turrets_[currentTurret_]->render(time);
}

