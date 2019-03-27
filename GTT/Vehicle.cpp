#include "Vehicle.h"
#include "Turret.h"
#include "AimAtCursorAC.h"
#include "ShootIC.h"
#include "ReloadInputComponent.h"
#include "ChangeWeaponIC.h"
#include "Reticule.h"
#include "InputMovement.h"

Vehicle::Vehicle(int x, int y, VehicleInfo r, KeysScheme k) {

	this->setWidth(r.width);
	this->setHeight(r.height);

	this->setPosition(Vector2D(x, y));

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(TAXI_HP);
	health_->setDamageOverTime(DMG_OVER_TIME, DMG_FREQUENCY);
	addLogicComponent(health_);

	shIC_ = new ShootIC();
	reIC_ = new ReloadInputComponent();
	aimC_ = new AimAtCursorAC();
	addInputComponent(new ChangeWeaponIC());

	for (int i = 0; i < MAXTURRETS; i++) {
		turrets_[i]=nullptr;
	}
	
	// Movement
	this->maxSpeed_ = r.velMax;
	this->maxBackwardSpeed_ = r.velBackwardMax;
	this->turnSpeed_ = r.turnSpeed;
	this->acceleration_ = r.acceleration;
	
	// Physics
	phyO_ = new PhysicObject (b2_dynamicBody , r.width, r.height, position_.x, position_.y);
	this->addLogicComponent(phyO_);
	
	// Control
	control_ = new InputMovement(k, this);
	this->addInputComponent(control_);
	this->addLogicComponent(control_);
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

ReloadInputComponent * Vehicle::GetReloadIC()
{
	return reIC_;
}

ShootIC * Vehicle::GetShootIC()
{
	return shIC_;
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
	shIC_->ChangeInputMode(turrets_[currentTurret_]->isAutomatic());
}
Turret * Vehicle::getCurrentTurret()
{
	return turrets_[currentTurret_];
}

void Vehicle::setPosition(const Vector2D & pos, bool force) {
	GameObject::setPosition(pos);

	if (force) {
		b2Vec2 nextPos = b2Vec2(pos.x, pos.y) +
			b2Vec2(phyO_->getOrigin().x * width_,
				phyO_->getOrigin().y * height_);

		nextPos = b2Vec2(nextPos.x * PHYSICS_SCALING_FACTOR,
			nextPos.y * PHYSICS_SCALING_FACTOR);

		phyO_->getBody()->SetTransform(nextPos, phyO_->getBody()->GetAngle());
	}
}

void Vehicle::handleInput(Uint32 time, const SDL_Event & event)
{	
	Container::handleInput(time, event);
	if(turrets_[currentTurret_]!=nullptr) turrets_[currentTurret_]->handleInput(time, event);
}

void Vehicle::update(Uint32 time) {	
	Container::update(time);

	if (turrets_[currentTurret_] != nullptr)
		turrets_[currentTurret_]->update(time);
}

void Vehicle::render(Uint32 time) {
	Container::render(time);

	if (turrets_[currentTurret_] != nullptr)
		turrets_[currentTurret_]->render(time);
}


PhysicObject * Vehicle::GetPhyO()
{
	return phyO_;
}

float32 Vehicle::GetMaxSpeed()
{
	return maxSpeed_;
}

float32 Vehicle::GetMaxBackwardSpeed()
{
	return maxBackwardSpeed_;
}

float32 Vehicle::GetTurnSpeed()
{
	return turnSpeed_;
}

float32 Vehicle::GetAcceleration()
{
	return acceleration_;
}