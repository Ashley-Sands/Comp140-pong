#pragma once

#include "Vector2.h"
#include "color.h"
#include <string>
#include "libraries/SDL2-2.0.7/include/SDL.h"

class SDL_Rect;
class SDL_Renderer;

class Transform
{
public:

	Transform();
	Transform(std::string na);
	Transform(Vector2 pos, Vector2 scale, std::string name);

	~Transform();

	std::string objName;

	///Position and scale
	SDL_Rect GetRect();
	void SetRect(Vector2 position, Vector2 size);

	Vector2 GetPosition();
	void SetPosition(Vector2 newPosition);
	void SetPositionX( float x_pos );
	void SetPositionY( float y_pos );

	void MoveTransform( float move_x, float move_y, int deltaTime = 1000);
	void MoveTransform(Vector2 moveAmount, int deltaTime = 1000);

	Vector2 GetSize();
	void SetSize(Vector2 newSize);

	/// Color
	Color* GetColor();
	void SetColor(int r, int g, int b, int a);

	// check if other object has collider with this object
	// @Param otherObject:		SDL_Rect of other object
	virtual bool OnCollision(Transform* otherObject);

	// render the transform to SDL Renderer
	virtual void Render(SDL_Renderer* renderer);

private:

	SDL_Rect positionRect;
	Vector2 position;			//set the position into a vector so we dont lose any position

protected:
	Color* color;
	float const collisionSolver = 6.0f ;

};

