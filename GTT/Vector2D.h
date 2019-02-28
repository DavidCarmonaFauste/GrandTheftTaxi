#pragma once
#include <iostream>
#include <Box2D/Box2D.h>

using namespace std;

class Vector2D: public b2Vec2 {
public:
	Vector2D() :b2Vec2() {};
	Vector2D(b2Vec2 v) :b2Vec2(v) {};
	Vector2D(float32 x, float32 y) : b2Vec2(x, y) {};
	virtual ~Vector2D() {};
	Vector2D operator/(float32 d) const;
	Vector2D operator*(float32 d) const;
	Vector2D operator-(float32 d) const;
	/*double operator *(const Vector2D& d) const;
	friend ostream& operator<<(ostream& os, const Vector2D &v);*/
};

