#pragma once

#include "Vector2.h"

class SDL_Rect;

class Transform
{
public:

	Transform();
	Transform(Vector2 pos, Vector2 scale);

	~Transform();

	SDL_Rect GetRect();
	Vector2 GetPosition();
	Vector2 GetSize();

private:

	SDL_Rect positionRect;

};

