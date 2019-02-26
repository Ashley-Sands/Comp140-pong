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

	MoveTransform((*moveDirection * speed) * (deltaTime/1000.0f) );

}

bool ball::OnCollision(Transform * otherObject)
{

	// find what edge we have collion on if any
	Vector2 other_topLeft = otherObject->GetPosition();
	Vector2 other_bottomRight = other_topLeft + otherObject->GetSize();
	
	Vector2 this_topLeft = GetPosition();
	Vector2 this_bottomRight = this_topLeft + GetSize();

	// if the dif is < 0 its able to collide in that direction
	int coll_top, coll_right, coll_bot, coll_left;

	coll_top = this_topLeft.y - other_bottomRight.y;
	coll_right = other_topLeft.x - this_bottomRight.x;

	coll_bot = other_topLeft.y - this_bottomRight.y;

	coll_left = this_topLeft.x - other_bottomRight.x;

	bool collision = false;

	std::cout << "Collision left: " << coll_left << " ## " << otherObject->objName << "\n";
	std::cout << "Collision right: " << coll_right << " ## " << otherObject->objName << "\n";

	// top/bottom collision
	if ((coll_top < 0 && coll_bot < 0) && (coll_left < 0 && coll_right < 0))
	{
		collision = true;
	}

	// left/right collision
	if ((coll_left < 0 && coll_right < 0) && (coll_top < 0 && coll_bot < 0))
	{
		moveDirection->x = -moveDirection->x;
		moveDirection->y = 0.25f;	// TODO: work out the angle from the center of the collision
		collision = true;
	}

	return collision;
}
