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

	MoveTransform((*moveDirection * speed) * (deltaTime / 1000.0f) );

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

	// find if we are colliding on any edge.
	if (coll_left < collisionSolver && coll_right < collisionSolver && coll_top < collisionSolver && coll_bot < collisionSolver)
	{
		// top / bottom collision
		if (coll_top > -collisionSolver || coll_bot > -collisionSolver)
		{
			moveDirection->y = -moveDirection->y;

			// correct y position.
			if (coll_top > -collisionSolver)
				MoveTransform(0, (collisionSolver - coll_top) + 0.25f);
			else
				MoveTransform(0, -((collisionSolver - coll_bot) + 0.25f) );

		}

		// left / right collision
		if (coll_left > -collisionSolver || coll_right > -collisionSolver)
		{
			moveDirection->x = -moveDirection->x;
			
			// work out the amount to move in on the y direction (from the center of the colliding object.
			if (coll_top > coll_bot)
				moveDirection->y = 0.6f - (((abs(coll_top) / (otherObject->GetSize().y / 2.0f))) * 0.6f);
			else
				moveDirection->y = -(0.6f - ((abs(coll_bot) / (otherObject->GetSize().y / 2.0f))) * 0.6f);

			// correct X position.
			if (coll_left > -collisionSolver)
				MoveTransform((collisionSolver - coll_left) + 0.25f, 0);
			else
				MoveTransform(-((collisionSolver - coll_right) + 0.25f), 0);

		}

		collision = true;
	}

	return collision;
}
