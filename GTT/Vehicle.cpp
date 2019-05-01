#include "Vehicle.h"

#include "AimAtCursorAC.h"
#include "ChangeWeaponIC.h"
#include "Reticule.h"
#include "InputMovement.h"

#include "Turret.h"
#include "ReloadInputComponent.h"
#include "ShootIC.h"

unique_ptr<Vehicle> Vehicle::instance_ = nullptr;

Vehicle::Vehicle(){
	currentTurret_ = 0;
}

Vehicle::~Vehicle() {

	delete phyO_; phyO_ = nullptr;
	delete sprite_; sprite_ = nullptr;
	delete health_; health_ = nullptr;
	
	for (int i = 0; i < MAXTURRETS; i++) {
		if (turrets_[i] != nullptr) {
			delete turrets_[i];
			turrets_[i] = nullptr;
		}
	}
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
	int i = 0;
	while (i < MAXTURRETS && turrets_[i] != nullptr)
		i++;
	if (i < MAXTURRETS) {
		currentTurret_ = i;
		turrets_[currentTurret_] = turret;
		Reticule::getInstance()->ChangeReticule(turrets_[currentTurret_]->GetReticule());
		turrets_[currentTurret_]->AttachToVehicle(this);
		turrets_[currentTurret_]->registerObserver(smLC_); //register for capture events_Type in TaxiSoundManagerCP
	}
	else {
		cout << "maximo numero de torretas alcanzado" << endl;
	}

}
void Vehicle::ChangeTurret()
{
	turrets_[currentTurret_]->CancelReload();
	currentTurret_ = (currentTurret_ + 1)% MAXTURRETS;
	while (turrets_[currentTurret_] == nullptr) {
		currentTurret_ = (currentTurret_ + 1) % MAXTURRETS;
	}
	Reticule::getInstance()->ChangeReticule(turrets_[currentTurret_]->GetReticule());
	shIC_->ChangeInputMode(turrets_[currentTurret_]->isAutomatic());
	turrets_[currentTurret_]->ResetChargeProgress();
}
Turret * Vehicle::getCurrentTurret()
{
	return turrets_[currentTurret_];
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

	if (alive_ && health_->getHealth() <= 0) {
		alive_ = false;
		deathTime_ = SDL_GetTicks();
	}
	if (!alive_ && SDL_GetTicks() - deathTime_ >= 500) {
		Respawn();
	}

}

bool Vehicle::receiveEvent(Event & e) {
	/*if (e.type_ == STARTED_MOVING_FORWARD) health_->setDamageOverTime(DMG_OVER_TIME_MOVING, DMG_FREQUENCY);
	else if (e.type_ == STOPPED_MOVING_FORWARD) health_->setDamageOverTime(DMG_OVER_TIME, DMG_FREQUENCY);*/

	switch (e.type_)
	{
	case STARTED_MOVING_FORWARD:
		health_->setDamageOverTime(DMG_OVER_TIME_MOVING, DMG_FREQUENCY);
		break;

	case STOPPED_BACK_MOVING_FORWARD:
		health_->setDamageOverTime(DMG_OVER_TIME, DMG_FREQUENCY);
		break;

	case TURN_LEFT:
		sprite_->setAnimation("leftTurn");
		break;

	case TURN_RIGHT:
		sprite_->setAnimation("rightTurn");
		break;

	case TURN_DEFAULT:
		sprite_->setAnimation("default");
		break;


	default:	
		break;
	}





	

	return true;
}

void Vehicle::SaveSpawnPoint(Vector2D spawn)
{
	spawnPosition_ = spawn;
}

void Vehicle::Respawn()
{
	Vehicle::getInstance()->setPosition(spawnPosition_);
	Vector2D v = spawnPosition_;
	Vehicle::getInstance()->GetPhyO()->getBody()->SetTransform(spawnPosition_.Multiply(PHYSICS_SCALING_FACTOR), 0);
	spawnPosition_ = v;
	health_->resetHealth();
	alive_ = true;
}


void Vehicle::render(Uint32 time) {
	Container::render(time);

	if (turrets_[currentTurret_] != nullptr)
		turrets_[currentTurret_]->render(time);
}


float32 Vehicle::GetMaxBackwardSpeed()
{
	return maxBackwardSpeed_;
}
float32 Vehicle::GetAcceleration()
{
	return acceleration_;
}


void Vehicle::initAtributtes(VehicleInfo r, KeysScheme k)
{
	this->setWidth(r.width);
	this->setHeight(r.height);

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "default");
	sprite_->loadAnimation(r.leftTurnPath, "leftTurn");
	sprite_->loadAnimation(r.rightTurnPath, "rightTurn");
	this->addRenderComponent(sprite_);
	sprite_->setAnimation("default");

	// Health
	health_ = new Health(TAXI_HP);
	health_->setDamageOverTime(DMG_OVER_TIME, DMG_FREQUENCY);
	addLogicComponent(health_);
	alive_ = true;


	shIC_ = new ShootIC();
	reIC_ = new ReloadInputComponent();
	aimC_ = new AimAtCursorAC();
	addInputComponent(new ChangeWeaponIC());


	// Movement
	this->maxSpeed_ = r.velMax;
	this->maxBackwardSpeed_ = r.velBackwardMax;
	this->turnSpeed_ = r.turnSpeed;
	this->acceleration_ = r.acceleration;

	// Physics
	phyO_ = new PhysicObject(b2_dynamicBody, r.width, r.height, position_.x, position_.y);
	phyO_->setCollisions(0, TAXI_CATEGORY);
	this->addLogicComponent(phyO_);

	// Control
	control_ = new InputMovement(k, this);
	this->addInputComponent(control_);
	this->addLogicComponent(control_);
	control_->registerObserver(this);

	//Sound
	smLC_ = new TaxiSoundManagerCP(this);
	this->addLogicComponent(smLC_);

	control_->registerObserver(smLC_);

	//turrets
	for (int i = 0; i < MAXTURRETS; i++) {
		turrets_[i] = nullptr;
	}
}