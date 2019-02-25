#include "Color.h"



Color::Color()
{

	// set r,g,b,a to default 0
	red = green = blue = alpha = 0;

}

Color::Color(int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
	alpha = 0;
}

Color::Color(int r, int g, int b, int a) : Color(r, g, b)
{
	alpha = a;
}


Color::~Color()
{
}
