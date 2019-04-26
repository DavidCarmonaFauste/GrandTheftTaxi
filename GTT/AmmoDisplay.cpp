#include "AmmoDisplay.h"
#include "Turret.h"
#include <string>
using namespace std;

AmmoDisplay::AmmoDisplay()
{
	setPosition(Vector2D(Game::getInstance()->getCamera(UI_CAMERA)->getWidth()*0.05, Game::getInstance()->getCamera(UI_CAMERA)->getHeight()*0.9));
	SDL_Color fontColor = SDL_Color();
	fontColor.r = 255; fontColor.g = 255; fontColor.b = 255;
	Font* f = new Font(FONT_COOLFONT, 80);
	currentAmmo_ = new Text(f, "", fontColor);
	currentAmmo_->setCamera(UI_CAMERA);
	addRenderComponent(currentAmmo_);
	currentAmmo_->setAutoPos(true);
	currentAmmo_->setAutoSize(false);
	currentAmmo_->setSize(100, 40);
}

void AmmoDisplay::update(Uint32 deltaTime)
{
	if(Vehicle::getInstance()->getCurrentTurret()!=nullptr)
	currentAmmo_->setText(to_string((int)(Vehicle::getInstance()->getCurrentTurret()->GetAmmo())) + " / " + to_string((int)(Vehicle::getInstance()->getCurrentTurret()->GetMaxAmmo())));
}


AmmoDisplay::~AmmoDisplay()
{
}
