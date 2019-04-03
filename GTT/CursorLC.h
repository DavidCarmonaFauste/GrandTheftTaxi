#pragma once
#include "LogicComponent.h"
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>

class CursorLC : public LogicComponent {
public:
	CursorLC();
	virtual void update(GameObject* o, Uint32 deltaTime);
	void push(std::list<Vector2D> &l, Vector2D v, string t);
	Vector2D find(std::list<Vector2D> l, int c);
	virtual ~CursorLC();
};

