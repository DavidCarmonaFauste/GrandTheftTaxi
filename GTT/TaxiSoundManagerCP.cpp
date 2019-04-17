#include "TaxiSoundManagerCP.h"
#include "Game.h"
#include "SoundManager.h"
#include "Vehicle.h"


TaxiSoundManagerCP::TaxiSoundManagerCP(Vehicle * v)
{
	v_ = v;
	s_ = Game::getInstance()->getSoundManager();

	//initialize count management
	count_1 = count_2 = count_3 = -1;



	start();

}

void TaxiSoundManagerCP::start()
{
	//play first sound
	if (s_ != nullptr)
	{
		cout << "Play start sound" << endl;
		channel_ = s_->playSound(TAXI_START, 0);
	}
}

void TaxiSoundManagerCP::update(GameObject * o, Uint32 deltaTime)
{
	//Taxi is Working (have combustible)
	if (!(s_->isSoundPlaying(channel_)) && count_1 == -1) {
		cout << "Play motor working sound" << endl;
		s_->pauseSound(channel_);
		channel_ = s_->playSound(TAXI_IDLE, -1);

		count_1 = 1;
	}

	//check car velocity
	//si el coche ha bajado de velocidad y no está acelerando y el coche no está en punto puerto
	if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 0.5 && count_2 == 1 && count_3 == -1) {
		s_->pauseSound(channel_);
		channel_ = s_->playSound(TAXI_IDLE, -1);
		count_3 = 1;
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

			count_2 = -1;
		}
		else {
			//si el coche ya ha hacelerado no reproduce nuevamente el sonido. ya está en bucle
			if (count_2 == -1) {
				s_->pauseSound(channel_);
				channel_ = s_->playSound(TAXI_1, -1);

				count_2 = 1;//avisa de que el coche ya ha acelerado
				count_3 = -1; //asegura que en el update vuelva al estado punto muerto cuando baje la velocidad
			}
			
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
