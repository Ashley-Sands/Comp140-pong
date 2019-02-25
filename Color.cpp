#include "Color.h"



Color::Color()
{

	// set r,g,b to default 0
	red = green = blue = 0;

}

Color::Color(int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
}

Color::~Color()
{
}
