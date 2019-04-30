#include "Enemy.h"
#include "Reticule.h"
#include "Vehicle.h"
#include "Turret.h"
#include "EnemyAim.h"


Enemy::Enemy()
{
}

Enemy::Enemy(VehicleInfo r, NodeMap* nmap, vector<Node*> route, Vector2D pos){
	this->setWidth(r.width);
	this->setHeight(r.height);

	position_ = pos;

	bodyReadyToDestroy_ = false;

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	//sprite_->playAnimation("idle");
	sprite_->setAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(ENEMY_HP);
	addLogicComponent(health_);

	//Movement
	speed_ = 5;

	// Physics
	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	phyO_->getBody()->SetUserData(this);
	addLogicComponent(phyO_);

	//IA
	pursuitRange_ = 32 * 40;
	patrolBehaviour_ = new IApatrol(GetPhyO(), this, nmap, speed_, route);
	addLogicComponent(patrolBehaviour_);
	aimC_ = new EnemyAim();

	turret_ = new Turret(GUN);
	turret_->AttachToVehicle(this);
}

void Enemy::Damage(double damage)
{
	health_->damage(damage);
	if (health_->getHealth() <= 0) Die();
}

void Enemy::Die()
{
	bodyReadyToDestroy_ = true;
	turret_->setActive(false);
}

void Enemy::update(Uint32 deltaTime)
{
	if (active_) {
		if (bodyReadyToDestroy_) {
			delLogicComponent(phyO_);
			delete phyO_;
			phyO_ = nullptr;
			setActive(false);
		}
		Car::update(deltaTime);
		if (turret_ != nullptr) {
			turret_->update(deltaTime);
		}
	}
}

void Enemy::render(Uint32 deltaTime)
{
	Car::render(deltaTime);

	if (turret_ != nullptr) {
		turret_->render(deltaTime);
	}
}

void Enemy::handleInput(Uint32 deltaTime, const SDL_Event & event)
{
	if (active_) {
		Car::handleInput(deltaTime, event);
	}
}

int Enemy::getDistanceFromTaxi()
{
	return (Vehicle::getInstance()->getCenter() - getCenter()).Length();
}

Turret * Enemy::getTurret()
{
	return turret_;
}

bool Enemy::taxiOnRange()
{
	return getDistanceFromTaxi()<=pursuitRange_;
}


Enemy::~Enemy()
{
	delete turret_;
}
