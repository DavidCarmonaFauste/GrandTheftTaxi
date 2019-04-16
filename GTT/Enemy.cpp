#include "Enemy.h"
#include "Reticule.h"


Enemy::Enemy(int x, int y, VehicleInfo r) :Car(x, y) {
	this->setWidth(r.width);
	this->setHeight(r.height);

	bodyReadyToDestroy_ = false;

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(ENEMY_HP);
	addLogicComponent(health_);

	//Movement
	speed_ = 5;
	//IA
	

	// Physics
	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	phyO_->getBody()->SetUserData(this);
	//phyO_->getBody()->SetLinearDamping(2.0f);
	//phyO_->getBody()->SetAngularDamping(2.0f);
	addLogicComponent(phyO_);
}

void Enemy::Damage(double damage)
{
	health_->damage(damage);
	if (health_->getHealth() <= 0) Die();
}

void Enemy::Die()
{
	bodyReadyToDestroy_ = true;
}

void Enemy::update(Uint32 deltaTime)
{
	if (active_) {
		if (destinated_) {
			if (direction_.x < 0) {
				if (getCenter().x < destination_.x) {
					phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
					destinated_ = false;
					return;
				}
			}
			else if (direction_.x > 0) {
				if (getCenter().x > destination_.x) {
					phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
					destinated_ = false;
					return;
				}
			}
			else if (direction_.y < 0) {
				if (getCenter().y < destination_.y) {
					phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
					destinated_ = false;
					return;
				}
			}
			else if (direction_.y > 0) {
				if (getCenter().y > destination_.y) {
					phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
					destinated_ = false;
					return;
				}
			}
			direction_ = Vector2D(destination_.x - getCenter().x, destination_.y - getCenter().y);
			direction_.Normalize();
			float angle = atan2f(-direction_.x, direction_.y);
			angle += 90.0 / 180.0*M_PI;
			phyO_->getBody()->SetTransform(phyO_->getBody()->GetPosition(), angle);
			phyO_->getBody()->SetLinearVelocity(Vector2D(direction_.x * speed_, direction_.y * speed_));
		}
		else {
			destinated_ = true;
			destination_ = route[node++%4];
			direction_ = Vector2D(destination_.x - getCenter().x, destination_.y - getCenter().y);
			direction_.Normalize();
		}
		if (bodyReadyToDestroy_) {
			delLogicComponent(phyO_);
			delete phyO_;
			phyO_ = nullptr;
			setActive(false);
		}
		Car::update(deltaTime);
	}
}

void Enemy::handleInput(Uint32 deltaTime, const SDL_Event & event)
{
	if (active_) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_RIGHT) {
				destinated_ = true;
				destination_ = Vector2D(Reticule::GetInstance()->getCenter().x + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().x,
					Reticule::GetInstance()->getCenter().y + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().y);
				direction_ = Vector2D(destination_.x - getCenter().x, destination_.y - getCenter().y);
				direction_.Normalize();
			}
		}
		Car::handleInput(deltaTime, event);
	}
}


Enemy::~Enemy()
{
}
