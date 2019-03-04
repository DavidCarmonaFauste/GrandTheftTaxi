#include "Reticule.h"
#include "Animation.h"
#include "CursorLC.h"


Reticule::Reticule()
{
	animations_["gun"] = "../Assets/sprites/gunreticule.png";//tantos como distintos sprites de reticula;
	animC_ = new Animation();
	cursorC_ = new CursorLC();
	addRenderComponent(animC_);
	addLogicComponent(cursorC_);
	for (auto o : animations_) {
		animC_->loadAnimation(o.second, o.first);//carga las distintas animaciones en el componente de render
	}
	
	height_ = 50;
	width_ = 50;
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
