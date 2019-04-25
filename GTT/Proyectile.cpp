#include "Proyectile.h"
#include "Vehicle.h"
#include "BounceImC.h"
#include "ExplosiveImC.h"
#include "ImpactComponent.h"


b2Filter Proyectile::colFilter = b2Filter();

Proyectile::Proyectile():Trigger(0,0,0,0)
{
	delLogicComponent(phyO_);
	delete phyO_;
	phyO_ = nullptr;

	bodyReadyToDestroy_ = false;
	setActive(false);
	colFilter.groupIndex = BULLETS_GROUP;
}


void Proyectile::SetBirth(double birthTime)
{
	birthTime_ = birthTime;
}


void Proyectile::update(Uint32 time)
{
	if (SDL_GetTicks() - birthTime_ >= lifeTime_) {
		DeactivateBullet();
	}
	if (bodyReadyToDestroy_) {
		delLogicComponent(phyO_);
		delete phyO_;
		phyO_ = nullptr;
		active_ = false;
	}
	Container::update(time);
}

void Proyectile::ChangeBulletType(ProyectileInfo p)
{
	if (phyO_ != nullptr) {
		delLogicComponent(phyO_);
		delete phyO_;
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

	bodyReadyToDestroy_ = false;
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
	phyO_->setCollisions(BULLETS_GROUP, BULLET_CATEGORY, ~(~0xFFFF | TAXI_CATEGORY) );
	phyO_->getBody()->GetFixtureList()->SetRestitution(1.0f);

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

double Proyectile::GetDamage()
{
	return damage_;
}

double Proyectile::GetSpeed()
{
	return speed_;
}

void Proyectile::DeactivateBullet()
{
	bodyReadyToDestroy_ = true;
}

