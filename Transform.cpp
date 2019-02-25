#include "Transform.h"


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
{
	delete color;
}

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
void Transform::Render(SDL_Renderer* renderer)
{

	// Render Rect to renderer.
	SDL_SetRenderDrawColor(renderer, color->red, color->green, color->blue, color->alpha);
	SDL_RenderFillRect(renderer, &positionRect);

}