#pragma once

#include "Vector2.h"

class Transform
{
public:

	Transform();
	Transform(Vector2* pos, Vector2* scale);

	~Transform();

	Vector2* position;
	Vector2* scale;

};

