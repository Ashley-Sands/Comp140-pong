#pragma once

#include "Transform.h"
#include "Vector2.h"

class ball : public Transform
{
public:
	ball();
	ball(Vector2 position, Vector2 size);

	~ball();

	void Update();

private:
	
	Vector2* moveDirection;

	int speed = 5;

};

