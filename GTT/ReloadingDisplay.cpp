#include "ReloadingDisplay.h"
#include "Game.h"
#include "Turret.h"


ReloadingDisplay::ReloadingDisplay(Vehicle* vehicle)
{
	vehicle_ = vehicle;
	setPosition(Vector2D(Game::getInstance()->getWindowWidth()-50, Game::getInstance()->getWindowHeight() -50));
	setWidth(200); setHeight(50);

	background = new Sprite("./../Assets/sprites/health_background.png");
	background->setCamera(UI_CAMERA);

	bar = new Sprite("./../Assets/sprites/health_bar.png");
	bar->setCamera(UI_CAMERA);
	bar->setAutoSize(false);
	bar->setSize(getWidth(), getHeight());

	addRenderComponent(background);
	addRenderComponent(bar);

	bar_clip = new SDL_Rect();
}

void ReloadingDisplay::setReloadingPercentage()
{
	Texture* tex = bar->getTexture();
	bar_clip->x = bar_clip->y = 0;
	bar_clip->w = tex->getWidth() * vehicle_->getCurrentTurret()->GetReloadPercentage();
	bar_clip->h = tex->getHeight();

	bar->setSize(getWidth() *  vehicle_->getCurrentTurret()->GetReloadPercentage(), getHeight());
	bar->setClipRect(bar_clip);
}

int ReloadingDisplay::getReloadingPercentage()
{
	return  vehicle_->getCurrentTurret()->GetReloadPercentage();
}


ReloadingDisplay::~ReloadingDisplay()
{
}

void ReloadingDisplay::update(Uint32 deltaTime)
{
	setReloadingPercentage();
}
