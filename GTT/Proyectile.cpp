#include "Proyectile.h"


Proyectile::Proyectile()
{
	animC_ = new Animation();
	animC_->loadAnimation(bulletPath_, "bullet");
	animC_->loadAnimation(flamePath_, "flame");//spritesheet (poner columnas y filas)
	animC_->loadAnimation(strikePath_, "strike");

	height_ = 50;
	width_ = 50;

	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	addLogicComponent(phyO_);
	addRenderComponent(animC_);
}


void Proyectile::Impact()//que hacer cuando el proyectil colisiona con algo
{
	active_ = false;
}

void Proyectile::SetDamage(double damage)
{
	damage_ = damage;
}

void Proyectile::SetLifeTime(double lifeTime)
{
	lifeTime_ = lifeTime;
}

void Proyectile::SetBirth(double birthTime)
{
	birthTime_ = birthTime;
}

void Proyectile::SetAnimation(proyectileType type)
{
	switch (type) {
	case BULLET:
		animC_->playAnimation("bullet");
		break;
	case FLAME:
		animC_->playAnimation("flame");
		break;
	case STRIKE:
		animC_->playAnimation("strike");
		break;
	default:
		break;
	}
}

void Proyectile::update(Uint32 time)
{
	if (SDL_GetTicks() - birthTime_ >= lifeTime_) {
		setActive(false);
	}
	Container::update(time);
}

PhysicObject * Proyectile::GetPhyO()
{
	return phyO_;
}

