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

	//ch_3MaxVel = false;
	ch_3KeyDown = false;
	ch_3KeyUp = false;

	start();

	ch_3_Vol_ = 68; //el valor de la variable por defecto hay que establecerlo como const global

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
		cout << "alcanza velocidad de aceleracion: " << endl;
		cout << "Taxi Velocity: " << v_->GetPhyO()->getBody()->GetLinearVelocity().Length() << endl;

	}

	else if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 1.2 && (s_->isSoundPlaying(channel_4))) {
		s_->stopSound(channel_4);
		cout << "alcanza velocidad reducida por defecto: " << endl;
		cout << "Taxi Velocity: " << v_->GetPhyO()->getBody()->GetLinearVelocity().Length() << endl;
	}

	//Volume Management
	//increase the volume of the acceleration until max aceleration velocity
	if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < 7.0 && (s_->isSoundPlaying(channel_3))) {

		if (ch_3_Vol_ < s_->getMIX_MAX_VOLUME()) {
			ch_3_Vol_ += 8;
			s_->setVolumeSound(channel_3, ch_3_Vol_);
		}
		cout << "Volume of " << channel_3 << ": " << ch_3_Vol_ << endl;
	}
	else if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() > 1.3 && (s_->isSoundPlaying(channel_4))) {
		if (ch_4_Vol_ >= 20) {
			ch_4_Vol_ -= 6;
			s_->setVolumeSound(channel_4, ch_4_Vol_);
		}
		cout << "Volume of " << channel_4 << ": " << ch_4_Vol_ << endl;
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
		}
		break;

	case STOPPED_MOVING_FORWARD:
		if (s_->isSoundPlaying(channel_3)) {
			ch_3KeyUp = true;
			s_->stopSound(channel_3);
		}
			
		else if (s_->isSoundPlaying(channel_5)) {
			ch_5KeyUp = true;
			s_->stopSound(channel_5);
		}			
		break;

	case BACK_MOVING_FORWARD:

		break;

	//callback receive from SoundManager when channel is stopped
	case CHANNEL_STOPPED_PLAYING: {
		ChannelStoppedPlaying channelEvent = static_cast<ChannelStoppedPlaying&>(e);	
		cout << "Channel " << channelEvent.channel_ << " stopped playing." << endl;

		//channel 1 = start car sound
		if (channelEvent.channel_ == 1) {
			s_->playSound_Ch(channel_2, TAXI_IDLE, -1);
			s_->setVolumeSound(channel_2, 70);
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
				if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() >= 3.5)
				{
					s_->playSound_Ch(channel_4, TAXI_DECELERATE_10, -1);
					ch_4_Vol_ = ch_3_Vol_; //recoge el valor del estado de aceleración actual
					s_->setVolumeSound(channel_4, ch_4_Vol_);
				}
				//regular engine sound
				else {
					s_->playSound_Ch(channel_2, TAXI_IDLE, -1);
					s_->setVolumeSound(channel_2, 70);
				}
				//reset default var values
				ch_3KeyUp = false;
				ch_3_Vol_ = 68; //el valor por defecto que ponerlo como sonst global
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

			else {
				s_->playSound_Ch(channel_2, TAXI_IDLE, -1);
				s_->setVolumeSound(channel_2, 70);
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
		}

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
