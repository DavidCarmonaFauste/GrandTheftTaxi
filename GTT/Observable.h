#pragma once

#include <vector>

using namespace std;

class Observer;

enum event_type {
	GAME_START,
	GAME_END,
	LENGTH
};

struct Event {
	event_type type;
};


class Observable
{
public:
	Observable();
	virtual ~Observable();

	void registerObserver(Observer* o);
	bool removeObserver(Observer* o);
	bool isRegistered(Observer* o, int &index);
	void cleanObservers();

protected:
	void broadcastEvent(Event *e);

private:
	vector<Observer*> observers;
};

