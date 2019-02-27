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

Transform::Transform(std::string name)
{
	objName = name;
	positionRect.x = 0;
	positionRect.y = 0;
	positionRect.w = 0;
	positionRect.h = 0;
	color = new Color();
}

Transform::Transform(Vector2 pos, Vector2 size, std::string name)
{
	positionRect.x = pos.x;
	positionRect.y = pos.y;
	positionRect.w = size.x;
	positionRect.h = size.y;
	color = new Color();

	objName = name;

}

Transform::~Transform()
{
	delete color;
}

SDL_Rect Transform::GetRect()
{
	// check that the position is upto date with the vector2
	positionRect.x = position.x;
	positionRect.y = position.y;

	return positionRect;
}

void Transform::SetRect(Vector2 position, Vector2 size)
{
	SetPosition(position);
	SetSize(size);
}

Vector2 Transform::GetPosition()
{
	return position;// Vector2(positionRect.x, positionRect.y);
}

void Transform::SetPosition(Vector2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
}

void Transform::SetPositionX(float x_pos)
{
	position.x = x_pos;
}

void Transform::SetPositionY(float y_pos)
{
	position.y = y_pos;
}

void Transform::MoveTransform(float move_x, float move_y, int deltaTime)
{
	MoveTransform( Vector2(move_x, move_y), deltaTime );
}

void Transform::MoveTransform(Vector2 moveAmount, int deltaTime)
{
	SetPosition( GetPosition() + (moveAmount * (deltaTime/1000.0f) ) );
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

Color* Transform::GetColor()
{
	return color;
}

void Transform::SetColor(int r, int g, int b, int a)
{
	color->red = r;
	color->green = g;
	color->blue = b;
	color->alpha = a;
}

bool Transform::OnCollision(Transform* otherObject)
{
	//TODO: applie collidion logic.
	return false;
}

void Transform::Render(SDL_Renderer* renderer)
{

	//update the rects x/y position
	positionRect.x = position.x;
	positionRect.y = position.y;

	// Render Rect to renderer.
	SDL_SetRenderDrawColor(renderer, color->red, color->green, color->blue, color->alpha);
	SDL_RenderFillRect(renderer, &positionRect);

}