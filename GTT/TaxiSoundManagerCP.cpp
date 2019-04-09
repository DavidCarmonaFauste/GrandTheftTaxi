#include "TaxiSoundManagerCP.h"
#include "Game.h"
#include "SoundManager.h"
#include "Vehicle.h"


TaxiSoundManagerCP::TaxiSoundManagerCP(Vehicle * v)
{
	v_ = v;
	s_ = Game::getInstance()->getSoundManager();
}

void TaxiSoundManagerCP::update(GameObject * o, Uint32 deltaTime)
{
	if (!s_->isSoundPlaying(channel_) && v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 0.5)
	{
		cout << "idle" << endl;
		channel_ = s_->playSound(TAXI_IDLE, 0);
	}
}

bool TaxiSoundManagerCP::receiveEvent(Event & e)
{
	switch (e.type_)
	{
	case STARTED_MOVING_FORWARD:
		if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 0.5)
		{
			if (s_->isSoundPlaying(channel_))
			{
				s_->pauseSound(channel_);
			}
			s_->playSound(TAXI_ACCELERATE_01, 0);
		}
			break;
	case STOPPED_MOVING_FORWARD:
		break;
	default:
		break;
	}
	return true;
}
 

TaxiSoundManagerCP::~TaxiSoundManagerCP()
{
}
