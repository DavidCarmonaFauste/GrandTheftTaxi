#include "GunProyectile.h"



GunProyectile::GunProyectile()
{
	animC_->loadAnimation("../Assets/sprites/bullet.png", "default");
	animC_->playAnimation("default");
	width_ = 25;
	height_ = 25;
	speed_ = 100;
	lifeTime_ = 1000;
	damage_ = 10;
	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	addLogicComponent(phyO_);
}


GunProyectile::~GunProyectile()
{
}
