#include "ball.h"



ball::ball() : Transform::Transform()
{
	moveDirection = new Vector2(1, 0);
}

ball::ball(Vector2 pos, Vector2 size) : Transform::Transform(pos, size)
{
	moveDirection = new Vector2(1, 0);
}

ball::~ball()
{
	delete moveDirection;
}

void ball::Update()
{

	MoveTransform( (*moveDirection * speed) );

}