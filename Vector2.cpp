#include "Vector2.h"



Vector2::Vector2()
{
	// set both x and y to 0 by default
	x = y = 0;
}

Vector2::Vector2(float axis_x, float axis_y)
{
	x = axis_x;
	y = axis_y;
}

Vector2::~Vector2()
{
}
