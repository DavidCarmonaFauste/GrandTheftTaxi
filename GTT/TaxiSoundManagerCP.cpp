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
	channel_4 = 4;
	channel_5 = 5;
	channel_6 = 6;

	ch_3KeyDown = ch_3KeyUp = ch_5KeyUp = ch_6_KeyDown = ch_6_KeyUp = false;
	DEBUG_ = true;


	start();

	//ESTO DEBE PASARSE COMO CONST GLOBAL PARA FACILITAR DISEÑO
	ch_2_Vol_ = 90;
	ch_3_Vol_ = 40;
	ch_6_Vol_ = 50;
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
	//Stop Sounds Management
	//el vehículo no sobrepasa la velocidad de 8.4 según conf. por defecto
	
	//if have considerable velocity and Taxi_acelerate is playing
	if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() > 7.0 && (s_->isSoundPlaying(channel_3))) {
		s_->stopSound(channel_3);
		if (DEBUG_)
			cout << "Vel. Max. Aceleration: " << v_->GetPhyO()->getBody()->GetLinearVelocity().Length() << endl;

	}

	else if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 1.2 && (s_->isSoundPlaying(channel_4))) {
		s_->stopSound(channel_4);
		if (DEBUG_)
			cout << "Vel. Min. Aceleration: " << v_->GetPhyO()->getBody()->GetLinearVelocity().Length() << endl;
	}

	//----------------------------------------------------//

	//Volume Management
	//increase the volume of the acceleration until max aceleration velocity
	if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 7.0 && (s_->isSoundPlaying(channel_3))) {

		if (ch_3_Vol_ < s_->getMIX_MAX_VOLUME()) {
			ch_3_Vol_ += 4;
			s_->setVolumeSound(channel_3, ch_3_Vol_);
		}
		if (DEBUG_)
			cout << "Volume of " << channel_3 << ": " << ch_3_Vol_ << endl;
	}
	else if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() > 1.3 && (s_->isSoundPlaying(channel_4))) {
		if (ch_4_Vol_ >= 20) {
			ch_4_Vol_ -= 6;
			s_->setVolumeSound(channel_4, ch_4_Vol_);
		}
		if (DEBUG_)
			cout << "Volume of " << channel_4 << ": " << ch_4_Vol_ << endl;
	}
	else if ((s_->isSoundPlaying(channel_6))) {
		if (ch_6_Vol_ <= 100) {
			ch_6_Vol_ += 4;
			s_->setVolumeSound(channel_6, ch_6_Vol_);
		}
	}

}

bool TaxiSoundManagerCP::receiveEvent(Event & e)
{

	switch (e.type_)
	{
	case STARTED_MOVING_FORWARD:

		if (!(s_->isSoundPlaying(channel_3)))
		{
			ch_3KeyDown = true;

			if (s_->isSoundPlaying(channel_2))
				s_->stopSound(channel_2); //stop regular engine sound

			else if (s_->isSoundPlaying(channel_4))
				s_->stopSound(channel_4); //stop regular engine sound	

			else if (s_->isSoundPlaying(channel_6))
				s_->stopSound(channel_6); //stop backforward sound
		}
		break;

		//----------------------------------------------------//

	case STOPPED_MOVING_FORWARD:
		if (s_->isSoundPlaying(channel_3)) {
			ch_3KeyUp = true;
			ch_3KeyDown = false;
			s_->stopSound(channel_3);
		}

		else if (s_->isSoundPlaying(channel_5)) {
			ch_5KeyUp = true;
			s_->stopSound(channel_5);
		}
		break;

		//----------------------------------------------------//

	case BACK_MOVING_FORWARD:
		//cuando se pulsa freno y que suene Frenada, puede estar sonando: aceleracion, maxVelEngine, Deceleration
		if (!(s_->isSoundPlaying(channel_6))) {
			ch_6_KeyDown = true;

			if (s_->isSoundPlaying(channel_3)) {
				s_->stopSound(channel_3);
			}

			else if (s_->isSoundPlaying(channel_4)) {
				s_->stopSound(channel_4);
			}

			else if (s_->isSoundPlaying(channel_5)) {
				s_->stopSound(channel_5);
			}
		}
		break;

		//----------------------------------------------------//

		//callback receive from SoundManager when channel is stopped
	case CHANNEL_STOPPED_PLAYING: {
		ChannelStoppedPlaying channelEvent = static_cast<ChannelStoppedPlaying&>(e);
		if (DEBUG_)
			cout << "Channel " << channelEvent.channel_ << " stopped playing." << endl;

		//channel 1 = start car sound
		if (channelEvent.channel_ == 1) {
			s_->playSound_Ch(channel_2, TAXI_IDLE, -1);
			s_->setVolumeSound(channel_2, ch_2_Vol_);
		}

		//channel 2 = regular engine sound
		else if (channelEvent.channel_ == 2) {
			s_->playSound_Ch(channel_3, TAXI_ACCELERATE_01, -1); //play engine aceleration sound
			s_->setVolumeSound(channel_3, ch_3_Vol_);
			ch_3KeyDown = false;
		}

		//channel 3 = engine aceleration 
		else if (channelEvent.channel_ == 3) {
			if (ch_3KeyUp) {
				//deceleration sound
				if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() >= 5.5)
				{
					s_->playSound_Ch(channel_4, TAXI_DECELERATE_10, -1);
					ch_4_Vol_ = ch_3_Vol_; //recoge el valor del estado de aceleración actual
					s_->setVolumeSound(channel_4, ch_4_Vol_);
				}
				//regular engine sound
				else {
					s_->playSound_Ch(channel_2, TAXI_IDLE, -1);
					s_->setVolumeSound(channel_2, ch_2_Vol_);
				}
				//reset default var values
				ch_3KeyUp = false;
				ch_3_Vol_ = 68; //el valor por defecto que ponerlo como sonst global
			}
			//BackForward
			else if (ch_6_KeyDown) {
				s_->playSound_Ch(channel_6, TAXI_BACK_MOVING_FORWARD, -1);
				s_->setVolumeSound(channel_6, ch_6_Vol_);
				ch_6_KeyDown = false;
			}
			//max speed
			else {
				s_->playSound_Ch(channel_5, TAXI_FASTDRIVE, -1);
				s_->setVolumeSound(channel_5, s_->getMIX_MAX_VOLUME());
			}
		}

		//channel 4 = engine decelerate 
		else if (channelEvent.channel_ == 4) {
			if (ch_3KeyDown) {
				s_->playSound_Ch(channel_3, TAXI_ACCELERATE_01, -1); //play engine aceleration sound
				s_->setVolumeSound(channel_3, ch_3_Vol_);
				ch_3KeyDown = false;
			}

			else if (ch_6_KeyDown) {
				s_->playSound_Ch(channel_6, TAXI_BACK_MOVING_FORWARD, -1);
				s_->setVolumeSound(channel_6, ch_6_Vol_);
				ch_6_KeyDown = false;
			}

			else {
				s_->playSound_Ch(channel_2, TAXI_IDLE, -1);
				s_->setVolumeSound(channel_2, ch_2_Vol_);
			}

		}

		else if (channelEvent.channel_ == 5) {
			if (ch_5KeyUp) {
				ch_3KeyDown = false;
				s_->playSound_Ch(channel_4, TAXI_DECELERATE_10, -1);
				ch_4_Vol_ = s_->getMIX_MAX_VOLUME(); //recoge el valor del estado de aceleración actual
				s_->setVolumeSound(channel_4, ch_4_Vol_);
				ch_5KeyUp = false;
			}
			else if (ch_6_KeyDown) {
				s_->playSound_Ch(channel_6, TAXI_BACK_MOVING_FORWARD, -1);
				s_->setVolumeSound(channel_6, ch_6_Vol_);
				ch_6_KeyDown = false;
			}
		}

		else if (channelEvent.channel_ == 6) {
			if (ch_3KeyDown) {
				s_->playSound_Ch(channel_3, TAXI_ACCELERATE_01, -1); //play engine aceleration sound
				s_->setVolumeSound(channel_3, ch_3_Vol_);
				ch_3KeyDown = false;
			}

			else {
				s_->playSound_Ch(channel_2, TAXI_IDLE, -1);
				s_->setVolumeSound(channel_2, ch_2_Vol_);
			}

		}

		break;
	}
								  //----------------------------------------------------//

	default:

		break;
	}
	return true;
}


TaxiSoundManagerCP::~TaxiSoundManagerCP()
{
}
