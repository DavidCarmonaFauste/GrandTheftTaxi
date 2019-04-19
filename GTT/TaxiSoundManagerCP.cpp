#include "TaxiSoundManagerCP.h"
#include "Game.h"
#include "SoundManager.h"
#include "Vehicle.h"


TaxiSoundManagerCP::TaxiSoundManagerCP(Vehicle * v)
{
	v_ = v;
	s_ = Game::getInstance()->getSoundManager();
	s_->registerObserver(this);

	channel_1 = 1;
	channel_2 = 2;
	channel_3 = 3;

	start();
}

void TaxiSoundManagerCP::start()
{
	//play first sound
	if (s_ != nullptr)
	{
		s_->playSound_Ch(channel_1, TAXI_START, 0);
		cout << "Play start sound" << endl;
	}
}

void TaxiSoundManagerCP::update(GameObject * o, Uint32 deltaTime)
{
	//cout << "Play motor working sound" << endl;

	//check car velocity
	//si el coche ha bajado de velocidad y no está acelerando y el coche no está en punto puerto
	if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 0.5) {
		
	}
}

bool TaxiSoundManagerCP::receiveEvent(Event & e)
{
	switch (e.type_)
	{
	case STARTED_MOVING_FORWARD:
		if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 0.6)
		{
				
		}
		else {
						
		}
			break;

	case STOPPED_MOVING_FORWARD:

		break;

	case CHANNEL_STOPPED_PLAYING: {
		ChannelStoppedPlaying channelEvent = static_cast<ChannelStoppedPlaying&>(e);
	
		cout << "Channel " << channelEvent.channel_ << " stopped playing.";
		break;
		}

	default:
	
		break;
	}


	return true;
}
 

TaxiSoundManagerCP::~TaxiSoundManagerCP()
{
}
