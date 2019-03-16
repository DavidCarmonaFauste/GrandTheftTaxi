#include "UI.h"

UI::UI() {
	UIElements_ = vector<GameObject*>();

	healthDisplay_ = new HealthDisplay();
	UIElements_.push_back(healthDisplay_);
}


UI::~UI() {

}

void UI::render(Uint32 deltaTime) {
	for (auto element : UIElements_) {
		element->render(deltaTime);
	}
}

bool UI::receiveEvent(Event * e) {
	if (e->type_ == HEALTH_CHANGED) {
		HealthChangedEvent* he = static_cast<HealthChangedEvent*>(e);
		healthDisplay_->setHealthPercentage((float) he->currentHealth_/he->maxHealth_);
	}

	return true;
}

