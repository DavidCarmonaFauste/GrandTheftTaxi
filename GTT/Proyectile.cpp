#include "Proyectile.h"
#include "Vehicle.h"
#include "BounceImC.h"
#include "ExplosiveImC.h"
#include "ImpactComponent.h"

Proyectile::Proyectile():Trigger(0,0,0,0)
{
	setActive(false);
}


void Proyectile::SetBirth(double birthTime)
{
	birthTime_ = birthTime;
}


void Proyectile::update(Uint32 time)
{
	if (SDL_GetTicks() - birthTime_ >= lifeTime_) {
		setActive(false);
	}
	Container::update(time);
}

void Proyectile::ChangeBulletType(ProyectileInfo p)
{
	if (phyO_ != nullptr) {
		delLogicComponent(phyO_);
		phyO_ = nullptr;
	}
	if (animC_ != nullptr) {
		delRenderComponent(animC_);
		animC_ = nullptr;
	}
	if (impC_ != nullptr) {
		delete impC_;
		impC_ = nullptr;
	}
	
	width_ = p.width;
	height_ = p.height;
	speed_ = p.speed;
	lifeTime_ = p.lifeTime;
	damage_ = p.damage;
	animC_ = new Animation();
	addRenderComponent(animC_);
	animC_->loadAnimation(p.idlePath, "default");
	animC_->playAnimation("default");
	phyO_ = new PhysicObject(b2_dynamicBody, width_, height_, position_.x, position_.y);
	switch (p.imp) {
	case STANDARD:
		phyO_->getBody()->GetFixtureList()->SetSensor(true);
		impC_ = new ImpactComponent(this);
		break;
	case BOUNCE:
		impC_ = new BounceImC(this);
		break;
	case EXPLOSIVE:
		phyO_->getBody()->GetFixtureList()->SetSensor(true);
		impC_ = new ExplosiveImC(this);
		break;
	default:
		break;
	}
	addLogicComponent(phyO_);
}

void Proyectile::beginCallback(b2Contact * contact)
{
	if(contact!=nullptr)
		if (this != nullptr)
			if (impC_ != nullptr)
				impC_->Impact(contact);
}

void Proyectile::endCallback(b2Contact * contact)
{

}

PhysicObject * Proyectile::GetPhyO()
{
	return phyO_;
}

double Proyectile::GetSpeed()
{
	return speed_;
}

