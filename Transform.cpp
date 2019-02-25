#include "Transform.h"



Transform::Transform()
{
	position = new Vector2();
	scale = new Vector2();
}

Transform::Transform(Vector2* pos, Vector2* size)
{
	position = pos;
	scale = size;
}

Transform::~Transform()
{
	// clean up our transfrom.
	delete position;
	delete scale;

}
