#pragma once

class Observable;

enum event_type {
	GAME_START,
	GAME_END,

	HEALTH_CHANGED,
	MONEY_CHANGED,
	RESPAWNED,
	STARTED_MOVING_FORWARD,
	STOPPED_MOVING_FORWARD,
	BACK_MOVING_FORWARD,
	CHANNEL_STOPPED_PLAYING,
	EVENTS_LENGTH
};

struct Event {
	Event(Observable *sender, event_type type) {
		this->type_ = type;
		this->sender_ = sender;
	}

	event_type type_;
	Observable* sender_;
};

struct HealthChangedEvent : public Event {
	HealthChangedEvent(Observable* sender, int currentHealth, int previousHealth, int maxHealth) :
		Event(sender, HEALTH_CHANGED){
		this->currentHealth_ = currentHealth;
		this->previousHealth_ = previousHealth;
		this->maxHealth_ = maxHealth;
	}

	int currentHealth_;
	int previousHealth_;
	int maxHealth_;
};

struct MoneyChangedEvent : public Event {
	MoneyChangedEvent(Observable* sender, int currentMoney, int previousMoney) :
		Event(sender, MONEY_CHANGED) {
		this->currentMoney_ = currentMoney;
		this->previousMoney_ = previousMoney;
	}

	int currentMoney_;
	int previousMoney_;
};

struct ChannelStoppedPlaying : public Event {
	ChannelStoppedPlaying(Observable* sender, int channel) : Event(sender, CHANNEL_STOPPED_PLAYING) {
		channel_ = channel;
	}

	int channel_;
};