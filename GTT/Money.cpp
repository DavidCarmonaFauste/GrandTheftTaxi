#include "Money.h"



Money::Money() {
	currentMoney_ = minimumMoney_;
}


Money::~Money() {

}

bool Money::receiveEvent(Event & e) {
	return false;
}

void Money::setCurrentMoney(int money) {
	MoneyChangedEvent e(this, money, currentMoney_);
	broadcastEvent(e);

	currentMoney_ = money > minimumMoney_ ? money : minimumMoney_;
}

void Money::setMinMoney(int money) {
	minimumMoney_ = money;
}

int Money::getCurrentMoney() {
	return currentMoney_;
}

int Money::getMinMoney() {
	return minimumMoney_;
}
