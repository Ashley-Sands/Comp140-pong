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

	///Position and scale
	SDL_Rect GetRect();
	void SetRect(Vector2 position, Vector2 size);

	Vector2 GetPosition();
	void SetPosition(Vector2 newPosition);
	void SetPositionX( float x_pos );
	void SetPositionY( float y_pos );

	void MoveTransform( float move_x, float move_y );
	void MoveTransform(Vector2 moveAmount);

	Vector2 GetSize();
	void SetSize(Vector2 newSize);

	/// Color
	Color* GetColor();
	void SetColor(int r, int g, int b, int a);

	// check if other object has collider with this object
	// @Param otherObject:		SDL_Rect of other object
	virtual bool HasCollision(Transform* otherObject);

	// render the transform to SDL Renderer
	virtual void Render(SDL_Renderer* renderer);

private:

	SDL_Rect positionRect;
	Color* color;
};

