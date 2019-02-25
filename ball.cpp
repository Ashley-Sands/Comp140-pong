#include "ball.h"



ball::ball() : Transform::Transform()
{}

ball::ball(Vector2 pos, Vector2 size) : Transform::Transform(pos, size)
{}

ball::~ball()
{
	delete moveDirection;
}

void ball::Update()
{

	MoveTransform( (*moveDirection * speed) );

}