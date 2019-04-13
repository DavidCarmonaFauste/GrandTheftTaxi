#include "Enemy.h"



Enemy::Enemy(int x, int y, VehicleInfo r, KeysScheme k) :Car(x, y) {
	this->setWidth(r.width);
	this->setHeight(r.height);



	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(ENEMY_HP);
	//health_->setDamageOverTime(DMG_OVER_TIME, DMG_FREQUENCY);
	addLogicComponent(health_);

	/*shIC_ = new ShootIC();
	reIC_ = new ReloadInputComponent();
	aimC_ = new AimAtCursorAC();
	addInputComponent(new ChangeWeaponIC());

	for (int i = 0; i < MAXTURRETS; i++) {
		turrets_[i] = nullptr;
	}*/

	 //Movement
		
	//IA
	

	// Physics
	phyO_ = new PhysicObject(b2_dynamicBody, width_, height_, position_.x, position_.y);
	addLogicComponent(phyO_);

	
}

Enemy::~Enemy()
{
}
