#include "Transform.h"
#include "libraries/SDL2-2.0.7/include/SDL.h"


Transform::Transform()
{
	// Set defaults to 0
	positionRect.x = 0;
	positionRect.y = 0;
	positionRect.w = 0;
	positionRect.h = 0;
}

Transform::Transform(Vector2 pos, Vector2 size)
{
	positionRect.x = pos.x;
	positionRect.y = pos.y;
	positionRect.w = size.x;
	positionRect.h = size.y;
}

Transform::~Transform()
{}

SDL_Rect Transform::GetRect()
{
	return positionRect;
}

Vector2 Transform::GetPosition()
{
	return Vector2(positionRect.x, positionRect.y);
}

Vector2 Transform::GetSize()
{
	return Vector2(positionRect.w, positionRect.h);
}
}