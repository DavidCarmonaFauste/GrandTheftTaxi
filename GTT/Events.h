#pragma once

class Observable;

enum event_type {
	GAME_START,
	GAME_END,

	HEALTH_CHANGED,
	RESPAWNED,

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