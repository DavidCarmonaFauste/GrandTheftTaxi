#include "ShotGunProyectile.h"



ShotGunProyectile::ShotGunProyectile()
{
	animC_->loadAnimation("../Assets/sprites/bullet.png", "default");
	animC_->playAnimation("default");
	width_ = 50;
	height_ = 50;
	speed_ = 100;
	lifeTime_ = 500;
	damage_ = 10;
	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	addLogicComponent(phyO_);
}


ShotGunProyectile::~ShotGunProyectile()
{
}
