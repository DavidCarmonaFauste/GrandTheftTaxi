#include "Enemy.h"
#include "Reticule.h"
#include "Vehicle.h"
#include "Turret.h"
#include "EnemyAim.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "TaxiSoundManagerCP.h"
#include "Money.h"


Enemy::Enemy(VehicleInfo r, NodeMap* nmap, vector<Node*> route, Vector2D pos, WeaponInfo weapon){
	this->setWidth(r.width);
	this->setHeight(r.height);

	position_ = pos;

	zombie_ = false; 
	alive_ = true;
	bodyReadyToDestroy_ = false;


	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->loadAnimation(r.diePath, "enemyDie", 4, 3);
	sprite_->setAnimation("idle");
	//sprite_->playAnimation("enemyDie", 24.0f, true);

	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(ENEMY_HP);
	addLogicComponent(health_);

	//Movement
	speed_ = 3;

	//Reward
	reward_ = r.reward;

	// Physics
	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	phyO_->setCollisions(0, ENEMY_CATEGORY);
	phyO_->getBody()->SetUserData(this);
	addLogicComponent(phyO_);

	//IA
	pursuitRange_ = 32 * 20;
	follow_ = new IAFollow(GetPhyO(), this, nmap, speed_);
	patrol_ = new IApatrol(GetPhyO(), this, nmap, speed_, route);
	addLogicComponent(patrol_);
	followmode_ = false;
	aimC_ = new EnemyAim();

	turret_ = new Turret(weapon);
	turret_->AttachToVehicle(this);
}

void Enemy::Damage(double damage)
{
	health_->damage(damage);
	if (health_->getHealth() <= 0 && !bodyReadyToDestroy_) {
		Vehicle::getInstance()->getHealthComponent()->heal(KILL_HEAL);
		GameManager::getInstance()->addKill();
		GameManager::getInstance()->decreaseEnemyCount();
		SoundManager::getInstance()->playSound_Ch(0, ENEMY_DIE, 0); //channel 0 for not interrupt other sounds
		//Send reward
		Money::getInstance()->addMoney(reward_);

		sprite_->playAnimation("enemyDie", 10.0f, false);
		bodyReadyToDestroy_ = true;
		turret_->setActive(false);
		turret_->setActive(false);
		zombie_ = true; //lanza el flag para que en el update se desactiven la l�gica de patruya
	}
}

void Enemy::Die()
{	
	setActive(false);
}

void Enemy::update(Uint32 deltaTime)
{
	if (active_) {
		if (bodyReadyToDestroy_) {
			delLogicComponent(phyO_);
			delete phyO_;
			phyO_ = nullptr;
		}


		if (!zombie_) {
			
				if (followmode_ != taxiOnRange()) {
					followmode_ = !followmode_;
					if (followmode_) {
						delLogicComponent(patrol_);
						addLogicComponent(follow_);
						follow_->Restart();
					}
					else {
						delLogicComponent(follow_);
						addLogicComponent(patrol_);
						patrol_->Restart();
					}
				}
				
			Car::update(deltaTime);
			if (turret_ != nullptr) {
				turret_->update(deltaTime);
			}
		}

		if (!sprite_->isAnimationPlaying("enemyDie") && zombie_) { 
			alive_ = false; 
		}

		if (!alive_) {
			Die();
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
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_p) {
				followmode_ = !followmode_;
				if (followmode_) {
					delLogicComponent(patrol_);
					addLogicComponent(follow_);
					follow_->Restart();
				}
				else {
					delLogicComponent(follow_);
					addLogicComponent(patrol_);
					patrol_->Restart();
				}
			}
		}
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

IAMovementBehaviour * Enemy::getIABehaviour()
{
	if (followmode_)
		return follow_;
	return patrol_;
}


Enemy::~Enemy()
{
	delete turret_;
}

