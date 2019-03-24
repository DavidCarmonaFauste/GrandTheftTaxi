#include "Reticule.h"
#include "Animation.h"
#include "CursorLC.h"
#include <map>

Reticule* Reticule::instance_ = nullptr;

Reticule::Reticule()
{
	animations_["gun"] = "../Assets/sprites/gunreticule.png";//tantos como distintos sprites de reticula;
	animations_["shotgun"] = "../Assets/sprites/shotgunreticule.png";
	animations_["machinegun"] = "../Assets/sprites/machinegunreticule.png";
	animations_["sniper"]= "../Assets/sprites/sniperreticule.png";

	animC_ = new Animation();
	cursorC_ = new CursorLC();
	addRenderComponent(animC_);
	addLogicComponent(cursorC_);
	for (auto o : animations_) {
		animC_->loadAnimation(o.second, o.first);//carga las distintas animaciones en el componente de render
	}
	
	height_ = 75;
	width_ = 75;
}


Reticule::~Reticule()
{
	delete animC_;
	delete cursorC_;
}

void Reticule::ChangeReticule(string ret)
{
	if (!animC_->playAnimation(ret)) cout << "ChangeReticule error, reticule: " + ret + " doesnt exist";
}

void Reticule::update(Uint32 time)
{
	Container::update(time);
}
