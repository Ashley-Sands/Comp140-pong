#include "ball.h"
#include "Vector2.h"
#include <iostream>


ball::ball() : Transform::Transform()
{
	moveDirection = new Vector2(1.0f, 0);
}

ball::ball(std::string name) : Transform::Transform(name)
{
	moveDirection = new Vector2(1.0f, 0);
}

ball::ball(Vector2 pos, Vector2 size, std::string name) : Transform::Transform(pos, size, name)
{
	moveDirection = new Vector2(1.0f, 0);
}

ball::~ball()
{
	delete moveDirection;
}

void ball::Update(int deltaTime)
{

	MoveTransform((*moveDirection * speed)) * (deltaTime/1000.0f) );

}

bool ball::OnCollision(Transform * otherObject)
{

	// find what edge we have collion on if any
	Vector2* other_topLeft = &otherObject->GetPosition();
	Vector2  other_bottomRight = *other_topLeft + otherObject->GetSize();
	
	Vector2* this_topLeft = &GetPosition();
	Vector2  this_bottomRight = *this_topLeft + GetSize();

	bool inXRange = this_topLeft->x < other_bottomRight.x && this_bottomRight.x > other_topLeft->x;
	bool inYRange = this_topLeft->y < other_bottomRight.y && this_bottomRight.y > other_topLeft->y;

	bool collision = false;

	if (this_topLeft->y < other_bottomRight.y && (other_bottomRight.y - this_topLeft->y) <= GetSize().y)	// top collision
	{
		moveDirection->y = -moveDirection->y;
		collision = true;
	}
	else if (this_bottomRight.y > other_topLeft->y && (this_bottomRight.y - other_topLeft->y) <= GetSize().y) // bottom collision
	{
		moveDirection->y = -moveDirection->y;
		collision = true;
	}

	if (this_topLeft->x < other_bottomRight.x && (other_bottomRight.x - this_topLeft->x) <= GetSize().x  && inYRange)							// left collision
	{
		std::cout << "Collision\n";
		moveDirection->x = 1.0f / 60.0f;			// TODO: use some sorta delta time fo all 1/60's
		moveDirection->y = -0.25f * (1.0f/60.0f);	// TODO: work out the angle from the center of the collision
		collision = true;
	}
	else if (this_bottomRight.x > other_topLeft->x && (this_bottomRight.x - other_topLeft->x) <= GetSize().x && inYRange) // right collision
	{
		std::cout << "Collision\n";

		moveDirection->x = -1 / 60.0f;
		moveDirection->y = 0.25f * (1.0f / 60.0f);	// TODO: work out the angle from the center of the collision

		collision = true;
	}



	return collision;
}
