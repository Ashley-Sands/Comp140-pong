#pragma once

#include "Transform.h"
#include "Vector2.h"

class ball : public Transform
{
public:
	ball();
	ball(std::string name);
	ball(Vector2 position, Vector2 size, std::string name);

	~ball();

	void Update(int deltaTime);

	virtual bool OnCollision(Transform* otherObject) override;

private:
	
	Vector2* moveDirection;

	int speed = 75;

};

