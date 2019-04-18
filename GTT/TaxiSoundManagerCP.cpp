#include "TaxiSoundManagerCP.h"
#include "Game.h"
#include "SoundManager.h"
#include "Vehicle.h"


TaxiSoundManagerCP::TaxiSoundManagerCP(Vehicle * v)
{
	v_ = v;
	s_ = Game::getInstance()->getSoundManager();

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
	//si el coche ha bajado de velocidad y no est� acelerando y el coche no est� en punto puerto
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

	default:
	
		break;
	}


	return true;
}
 

TaxiSoundManagerCP::~TaxiSoundManagerCP()
{
}
