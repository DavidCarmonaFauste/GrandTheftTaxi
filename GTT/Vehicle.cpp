#include "Vehicle.h"
#include "Turret.h"
#include "NaturalMove.h"
#include "AimAtCursorAC.h"
#define PI 3.14159265359

Vehicle::Vehicle(Resources::VehicleId id) {
	Resources::VehicleInfo& r = Resources::vehicles_[id];

	this->setWidth(r.width);
	this->setHeight(r.height);

	setPosition(Vector2D(100, 0));

	// Physics
	/*
	phyO_ = new PhysicObject (b2_dynamicBody , r.width, r.height,
							  position_.getX(), position_.getY());
	this->addLogicComponent(phyO_);
	*/

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
void Vehicle::handleInput(Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {

		if (event.key.keysym.sym == SDLK_w) upPressed = true;

		if (event.key.keysym.sym == SDLK_s) downPressed = true;

		if (event.key.keysym.sym == SDLK_d) rightPressed = true;

		if (event.key.keysym.sym == SDLK_a) leftPressed = true;

		if (event.key.keysym.sym == SDLK_SPACE) spacePressed = true;

	}

	else if (event.type == SDL_KEYUP) {

		if (event.key.keysym.sym == SDLK_w) upPressed = false;

		if (event.key.keysym.sym == SDLK_s) downPressed = false;

		if (event.key.keysym.sym == SDLK_d) rightPressed = false;

		if (event.key.keysym.sym == SDLK_a) leftPressed = false;

		if (event.key.keysym.sym == SDLK_SPACE) spacePressed = false;

	}
	currentTurret_->handleInput(time, event);
	Container::handleInput(time, event);
}

void Vehicle::update(Uint32 time)
{
	velocity_.normalize();

	if (downPressed) {

		if (speed_ > velMaxMarchaAtras_) speed_ = speed_ - aceleracion_;

	}

	if (rightPressed) {

		if (isMoving_()) steeringWheel('R');

		if (spacePressed) handBrake_ = true;

	}

	if (leftPressed) {

		if (isMoving_()) steeringWheel('L');

		if (spacePressed) handBrake_ = true;

	}

	if (!spacePressed) {

		handBrake_ = false;

		double rotationRadiant = (rotation_ * PI) / 180.0;

		if (rotation_ <= 180) velocity_.setX(abs(sin(rotationRadiant) * 2));

		else velocity_.setX(-abs(sin(rotationRadiant) * 2));

		if (rotation_ >= 90 && rotation_ <= 270)velocity_.setY(abs(cos(rotationRadiant) * 2));

		else velocity_.setY(-abs(cos(rotationRadiant) * 2));

	}

	if (!handBrake_)

		position_ = position_ + velocity_ * speed_;

	else

		position_ = position_ + velocity_ * speed_ / 1.5;



	// when exiting from one side appear in the other	/////////////////////////////////////////////////////////////////////////////////////// DELETE!

	if (position_.getX() >= 1280) {

		position_.setX(1 - width_);

	}

	else if (position_.getX() + width_ <= 0) {

		position_.setX(1280);

	}

	if (position_.getY() >= 720) {

		position_.setY(1 - height_);

	}

	else if (position_.getY() + height_ <= 0) {

		position_.setY(720);

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// DELETE!

				//Aceleration//

	if (!upPressed)

		frictionalForce();

	else if (speed_ < velMax_)

		speed_ = speed_ + aceleracion_;



	if (abs(speed_) < min_Velocity) {

		speed_ = 0;

	}
	currentTurret_->update(time);
	Container::update(time);
}

void Vehicle::render(Uint32 time)
{
	Container::render(time);
	currentTurret_->render(time);
}


bool Vehicle::isMoving_()
{
	return abs(speed_) > 0.2;
}

void Vehicle::frictionalForce()
{
	if (speed_ > 0)

	{

		speed_ = speed_ - constanteRozamiento_;

	}

	else if (speed_ < 0)

	{

		speed_ = speed_ + constanteRozamiento_;

	}
}

void Vehicle::steeringWheel(char d)
{
	if (d == 'R') {

		rotation_ = ((int)rotation_ + 360 + velGiro_) % 360;

		if (handBrake_) velocity_ = velocity_.rotate((velGiro_ - drift_));

		else velocity_ = velocity_.rotate(velGiro_);

	}

	else if (d == 'L') {

		rotation_ = ((int)rotation_ + 360 - velGiro_) % 360;

		if (handBrake_) velocity_ = velocity_.rotate(-(velGiro_ - drift_));

		else velocity_ = velocity_.rotate(-velGiro_);

	}
}

void Vehicle::setPosition(const Vector2D & pos, bool force) {
	GameObject::setPosition(pos);

	if (force) {
		b2Vec2 nextPos = b2Vec2(pos.getX(), pos.getY()) + 
						 b2Vec2(phyO_->getOrigin().x * width_,
							   phyO_->getOrigin().y * height_);

		nextPos = b2Vec2(nextPos.x * Resources::physicsScalingFactor,
						 nextPos.y * Resources::physicsScalingFactor);

		phyO_->getBody()->SetTransform(nextPos, phyO_->getBody()->GetAngle());
	}
}

