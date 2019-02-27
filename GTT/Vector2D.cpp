#include "Vector2D.h"
#include <SDL_assert.h>

// needed for visual studio
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

Vector2D Vector2D::operator/(double d) const
{
	Vector2D v;
	v.x = v.x / d;
	v.y = v.y / d;
	return v;
}
