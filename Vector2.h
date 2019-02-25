#pragma once
class Vector2
{
public:
	
	Vector2();
	Vector2(float axis_x, float axis_y);
	
	~Vector2();

	Vector2 operator + (Vector2 rhs);
	Vector2 operator - (Vector2 rhs);
	Vector2 operator * (Vector2 rhs);
	Vector2 operator * (float rhs);

	// define axis
	float x;
	float y;

};

