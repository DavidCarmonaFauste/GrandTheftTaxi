#include "Reticule.h"
#include "Animation.h"
#include "CursorLC.h"
#include <map>

Reticule* Reticule::instance_ = nullptr;

Reticule::Reticule()
{
	animations_["gun"] = PATH_RETICULE;//tantos como distintos sprites de reticula;
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
