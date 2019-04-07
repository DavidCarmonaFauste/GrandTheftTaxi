#include "TaxiSoundManagerCP.h"
#include "Game.h"
#include "SoundManager.h"
#include "Vehicle.h"


TaxiSoundManagerCP::TaxiSoundManagerCP()
{
}

void TaxiSoundManagerCP::Start()
{
	s_ = Game::getInstance()->getSoundManager();
	s_->playSound(TAXI_START,0);
}

void TaxiSoundManagerCP::update(GameObject * o, Uint32 deltaTime)
{

}


TaxiSoundManagerCP::~TaxiSoundManagerCP()
{
}
