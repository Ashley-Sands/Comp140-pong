#include "Transform.h"


Transform::Transform()
{
	// Set defaults to 0
	positionRect.x = 0;
	positionRect.y = 0;
	positionRect.w = 0;
	positionRect.h = 0;
	color = new Color();
}

Transform::Transform(Vector2 pos, Vector2 size)
{
	positionRect.x = pos.x;
	positionRect.y = pos.y;
	positionRect.w = size.x;
	positionRect.h = size.y;
	color = new Color();
}

Transform::~Transform()
{
	delete color;
}

SDL_Rect Transform::GetRect()
{
	return positionRect;
}

void Transform::SetRect(Vector2 position, Vector2 size)
{
	SetPosition(position);
	SetSize(size);
}

Vector2 Transform::GetPosition()
{
	return Vector2(positionRect.x, positionRect.y);
}

void Transform::SetPosition(Vector2 position)
{
	positionRect.x = position.x;
	positionRect.y = position.y;
}

Vector2 Transform::GetSize()
{
	return Vector2(positionRect.w, positionRect.h);
}

void Transform::SetSize(Vector2 size)
{
	positionRect.w = size.x;
	positionRect.h = size.y;
}
void Transform::Render(SDL_Renderer* renderer)
{

	// Render Rect to renderer.
	SDL_SetRenderDrawColor(renderer, color->red, color->green, color->blue, color->alpha);
	SDL_RenderFillRect(renderer, &positionRect);

}