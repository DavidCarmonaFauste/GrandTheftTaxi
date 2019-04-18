#include "TaxiSoundManagerCP.h"
#include "Game.h"
#include "SoundManager.h"
#include "Vehicle.h"


TaxiSoundManagerCP::TaxiSoundManagerCP(Vehicle * v)
{
	v_ = v;
	s_ = Game::getInstance()->getSoundManager();

	s_->registerObserver(this);

	//initialize count management
	count_1 = -1;

	start();
}

void TaxiSoundManagerCP::start()
{
	//play first sound
	if (s_ != nullptr)
	{
		cout << "Play start sound" << endl;
		//channel_1 = s_->playSound(TAXI_START, 0);
	
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
