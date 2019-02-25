#pragma once

#include "Vector2.h"
#include "color.h"
#include "libraries/SDL2-2.0.7/include/SDL.h"

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

	// render the transform to SDL Renderer
	virtual void Render(SDL_Renderer* renderer);

private:

	SDL_Rect positionRect;
	Color* color;
};

