#include "ReloadingDisplay.h"
#include "Game.h"
#include "Turret.h"


ReloadingDisplay::ReloadingDisplay()
{
	setPosition(Vector2D(Game::getInstance()->getWindowWidth()-40, 30));
	setWidth(200); setHeight(50);

	background = new Sprite("./../Assets/sprites/ReloadBarBackground.png");
	background->setCamera(UI_CAMERA);

	bar = new Sprite("./../Assets/sprites/ReloadBar.png");
	bar->setCamera(UI_CAMERA);
	bar->setAutoSize(false);
	bar->setAutoPos(false);
	
	bar->setSize(getWidth()*0.875, getHeight());
	bar->setPos(getPosition().x+0.0625*getWidth(), getPosition().y);
	barWidth = bar->getRect()->w;

	perfReSegment = new Sprite("./../Assets/sprites/PerfReInd.png");
	perfReSegment->setCamera(UI_CAMERA);
	perfReSegment->setAutoSize(false);
	perfReSegment->setAutoPos(false);

	addRenderComponent(bar);
	addRenderComponent(background);
	addRenderComponent(perfReSegment);

	bar_clip = new SDL_Rect();
}

void ReloadingDisplay::setReloadingPercentage()
{
	Texture* tex = bar->getTexture();
	bar_clip->x = bar_clip->y = 0;
	bar_clip->w = tex->getWidth() * Vehicle::GetInstance()->getCurrentTurret()->GetReloadPercentage();
	bar_clip->h = tex->getHeight();

	bar->setSize(barWidth *  Vehicle::GetInstance()->getCurrentTurret()->GetReloadPercentage(), getHeight());
	bar->setClipRect(bar_clip);
	perfReSegment->setSize(barWidth*Vehicle::GetInstance()->getCurrentTurret()->GetPerfReloadSeg(), getHeight());
	perfReSegment->setPos(bar->getRect()->x + barWidth* Vehicle::GetInstance()->getCurrentTurret()->GetPerfReloadIni(), getPosition().y);
}

ReloadingDisplay::~ReloadingDisplay()
{
	delete bar;
	delete background;
	delete perfReSegment;
}

void ReloadingDisplay::update(Uint32 deltaTime)
{
	if(active_)
		setReloadingPercentage();
}

void ReloadingDisplay::render(Uint32 deltaTime)
{
	if (active_)
		Container::render(deltaTime);
}

bool ReloadingDisplay::isReloading()
{
	return Vehicle::GetInstance()->getCurrentTurret()->isReloading();
}
