#include "AmmoDisplay.h"
#include "Turret.h"
#include <string>
using namespace std;

AmmoDisplay::AmmoDisplay(Vehicle* v)
{
	setPosition(Vector2D(Game::getInstance()->getWindowWidth()*0.05, Game::getInstance()->getWindowHeight()*0.9));
	vehicle_ = v;
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
	currentAmmo_->setText(to_string((int)(vehicle_->getCurrentTurret()->GetAmmo())) + " / " + to_string((int)(vehicle_->getCurrentTurret()->GetMaxAmmo())));
}


AmmoDisplay::~AmmoDisplay()
{
}
